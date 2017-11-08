/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:44:37 by amathias          #+#    #+#             */
/*   Updated: 2017/11/08 20:33:03 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	display_header_info(t_env *e)
{
	char ip[INET_ADDRSTRLEN];

	inet_ntop(e->addr->ai_family,
			&((struct sockaddr_in *)e->addr->ai_addr)->sin_addr, ip, sizeof(ip));

	printf("PING %s (%s) %lu(%lu) bytes of data.\n", e->hostname, ip,
			sizeof(t_rpacket) - sizeof(struct icmp), sizeof(t_rpacket));
}

/*
void	display_response(t_env *e, int bytes_receive, int seq, double duration)
{
	char ip[INET_ADDRSTRLEN];

	inet_ntop(e->addr->ai_family,
			&((struct sockaddr_in *)e->addr->ai_addr)->sin_addr, ip, sizeof(ip));
	if (ft_strcmp(ip, e->hostname) == 0 || e->flag.numeric_out)
	{
		printf("%u bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n",
				bytes_receive, ip, seq, e->flag.ttl, duration);
	}
	else
	{
		printf("%u bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3lf ms\n",
				bytes_receive, e->hostname, ip, seq, e->flag.ttl, duration);
	}
} */
