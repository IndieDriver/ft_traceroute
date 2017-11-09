/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:49:46 by amathias          #+#    #+#             */
/*   Updated: 2017/11/09 17:32:45 by amathias         ###   ########.fr       */
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
	hints.ai_socktype = SOCK_RAW;
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	s = getaddrinfo(addr, NULL, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
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
	e->socket = X(-1, socket(PF_INET, SOCK_RAW, IPPROTO_ICMP), "socket");
	//res = setsockopt(e->socket, IPPROTO_IP, IP_TTL, &e->flag.ttl,
	//		sizeof(e->flag.ttl));
}

void	ping_send(t_env *e, struct timeval *send_time, uint16_t sequence, uint32_t ttl)
{
	t_packet		packet;

	ft_memset(&packet, 0, sizeof(t_packet));
	packet.icmp.icmp_type = (uint8_t)ICMP_ECHO;
	packet.icmp.icmp_code = (uint8_t)0;
	packet.icmp.icmp_id = swap_byte16_t((uint16_t)getpid());
	packet.icmp.icmp_seq = swap_byte16_t((uint16_t)sequence);
	for (int i = 0; i < 36; i++)
		packet.data[i] = 10 + i;
	packet.icmp.icmp_cksum = checksum((uint16_t*)&packet, sizeof(t_packet));
	int res = setsockopt(e->socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	if (res == -1)
	{
		fprintf(stderr, "Can't set TTL\n");
	}
	sendto(e->socket, &packet, sizeof(t_packet), 0,
			e->addr->ai_addr, e->addr->ai_addrlen);
	e->sent++;
	gettimeofday (send_time, NULL);
}

int		ping_receive(t_env *e, struct timeval send_time, uint16_t sequence)
{
	struct sockaddr_storage	sender;
	socklen_t				fromlen;
	t_rpacket				received;
	int						byte_recv;

	(void)send_time;
	(void)sequence;
	if (e->has_timeout)
	{
		e->has_timeout = 0;
		alarm(0);
		display_response(e, sequence, NULL);
		return (1);
	}
	fromlen = sizeof(struct sockaddr_storage);
	if ((byte_recv = recvfrom(e->socket, &received, sizeof(t_rpacket),
					MSG_DONTWAIT, (struct sockaddr*)&sender, &fromlen)) > 0)
	{
		if (received.icmp.icmp_type == ICMP_ECHO)
			return (0);
		display_response(e, sequence, (struct sockaddr_in*)&sender);
		if (received.icmp.icmp_type == ICMP_ECHOREPLY)
			exit(0);
		alarm(0);
		ft_sleep(1);
		return (1);
	}
	return (0);
}

void	ping_host(t_env *e)
{
	int sequence;
	struct timeval send_time;

	sequence = 0;
	gettimeofday (&e->start_time, NULL);
	ping_connect(e);
	while (sequence <= 30)
	{
		sequence++;
		ping_send(e, &send_time, (uint16_t)sequence, sequence);
		alarm(1);
		while (!ping_receive(e, send_time, sequence))
			;
	}
}

int main(int argc, char *argv[])
{
	ft_memset(&g_env, 0, sizeof(t_env));
	g_env.ping_min = 1000.0;
	get_opt(&g_env, argc, argv);
	if (getuid() != 0)
	{
		fprintf(stderr, "Command need to be run as root\n");
		exit(1);
	}
	get_sockaddr(&g_env, g_env.hostname);
	display_header_info(&g_env);
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	ping_host(&g_env);
	freeaddrinfo(g_env.addr);
	return 0;
}
