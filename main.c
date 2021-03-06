/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:49:46 by amathias          #+#    #+#             */
/*   Updated: 2017/11/22 09:36:28 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	get_sockaddr(t_env *e, const char *addr)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	if (e->flag.icmp_mode)
	{
		hints.ai_socktype = SOCK_RAW;
		hints.ai_protocol = IPPROTO_ICMP;
	}
	else
	{
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;
	}
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	s = getaddrinfo(addr, NULL, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "traceroute: unknow host %s\n", addr);
		exit(EXIT_FAILURE);
	}
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;
		close(sfd);
		break ;
	}
	if (rp == NULL) {
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}
	e->addr = result;
}

void	ping_connect(t_env *e)
{
	struct timeval timeout;

	e->icmp_socket = X(-1, socket(PF_INET, SOCK_RAW, IPPROTO_ICMP), "socket");
	if (!e->flag.icmp_mode)
		e->udp_socket = X(-1, socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP), "socket");
	timeout.tv_sec = 0;
	timeout.tv_usec = 500000;

	setsockopt(e->icmp_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
}

void	ping_send(t_env *e, struct timeval *send_time, uint16_t sequence, uint32_t ttl)
{
	t_packet			packet;
	struct sockaddr_in	dest;
	int					sock;

	ft_memset(&packet, 0, sizeof(t_packet));
	packet.icmp.icmp_type = (uint8_t)ICMP_ECHO;
	packet.icmp.icmp_code = (uint8_t)0;
	packet.icmp.icmp_id = e->pid_be;
	packet.icmp.icmp_seq = swap_byte16_t((uint16_t)sequence);
	for (int i = 0; i < 36; i++)
		packet.data[i] = 10 + i;
	packet.icmp.icmp_cksum = checksum((uint16_t*)&packet, sizeof(t_packet));
	sock = e->flag.icmp_mode ? e->icmp_socket : e->udp_socket;
	int res = setsockopt(sock, IPPROTO_IP, IP_TTL,
			(char*)&ttl, sizeof(char));
	if (res == -1)
		fprintf(stderr, "Can't set TTL\n");
	ft_memcpy(&dest, e->addr->ai_addr, e->addr->ai_addrlen);
	if (!e->flag.icmp_mode)
		dest.sin_port = htons(e->flag.start_port++);
	sendto(sock, &packet, sizeof(t_packet), 0,
			(struct sockaddr*)&dest, sizeof(struct sockaddr));
	e->sent++;
	gettimeofday (send_time, NULL);
}

void	add_result(t_env *e, struct sockaddr_storage sender)
{
	struct timeval			received_time;

	for (int i = 0; i < 3; i++)
	{
		if (!e->result[i].has_completed)
		{
			gettimeofday(&received_time, NULL);
			e->result[i].has_completed = 1;
			e->result[i].res = get_time_elapsed(&e->result[i].send_time,
					&received_time);
			e->result[i].addr = sender;
			break ;
		}
	}
}

int		ping_receive(t_env *e)
{
	struct sockaddr_storage	sender;
	socklen_t				fromlen;
	t_rpacket				received;
	int						byte_recv;
	int						has_finish;

	has_finish = 0;
	fromlen = sizeof(struct sockaddr_storage);
	if ((byte_recv = recvfrom(e->icmp_socket, &received, sizeof(t_rpacket),
					0, (struct sockaddr*)&sender, &fromlen)) > 0)
	{
		if (is_same_host((struct sockaddr_in*)&sender,
					(struct sockaddr_in*)e->addr->ai_addr))
		{
			e->end = 1;
			add_result(e, sender);
			return (has_results(e));
		}
		else if (received.icmp.icmp_type == ICMP_ECHO)
			return (0);
		else if (received.icmp.icmp_type == ICMP_ECHOREPLY
				&& received.icmp.icmp_id == e->pid_be)
			e->end = 1;
		if (received.icmp.icmp_type == ICMP_TIME_EXCEEDED
				|| received.icmp.icmp_type == ICMP_ECHOREPLY)
		{
			add_result(e, sender);
			return (has_results(e));
		}
	} else {
		for (int i = 0; i < 3; i++)
		{
			if (!e->result[i].has_completed)
			{
				e->result[i].has_completed = 1;
				e->result[i].res = 0;
				break ;
			}
		}
		has_finish = has_results(e);
		if (has_finish)
		{
			e->has_timeout = 0;
		}
		return (has_finish);

	}
	return (has_results(e));
}

void	ping_host(t_env *e)
{
	int sequence;

	sequence = e->flag.start_ttl;
	if (sequence != 0)
		sequence--;
	gettimeofday (&e->start_time, NULL);
	ping_connect(e);
	while (sequence < e->flag.max_hop)
	{
		sequence++;
		ft_memset(e->result, 0, sizeof(e->result));
		ping_send(e, &e->result[0].send_time, (uint16_t)sequence, sequence);
		ping_send(e, &e->result[1].send_time, (uint16_t)sequence, sequence);
		ping_send(e, &e->result[2].send_time, (uint16_t)sequence, sequence);
		while (!ping_receive(e))
			;
		display_response(e, sequence);
		if (e->end)
			exit(0);
	}
}

int main(int argc, char *argv[])
{
	ft_memset(&g_env, 0, sizeof(t_env));
	g_env.flag.max_hop = 30;
	g_env.flag.start_port = 33453;
	if (getuid() != 0)
	{
		fprintf(stderr, "Command need to be run as root\n");
		exit(1);
	}
	get_opt(&g_env, argc, argv);
	get_sockaddr(&g_env, g_env.hostname);
	g_env.pid_be = swap_byte16_t(getpid());
	display_header_info(&g_env);
	ping_host(&g_env);
	return 0;
}
