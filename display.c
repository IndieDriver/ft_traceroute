/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:44:37 by amathias          #+#    #+#             */
/*   Updated: 2017/11/10 10:07:20 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	display_header_info(t_env *e)
{
	char ip[INET_ADDRSTRLEN];

	inet_ntop(e->addr->ai_family,
			&((struct sockaddr_in *)e->addr->ai_addr)->sin_addr, ip, sizeof(ip));
	printf("traceroute to %s (%s), %d hops max, %lu byte packets\n", e->hostname, ip,
			e->flag.max_hop, sizeof(t_rpacket) - sizeof(struct icmp));
}

void	display_address(struct sockaddr_in *addr)
{
	char ip[INET_ADDRSTRLEN];

	inet_ntop(addr->sin_family,
			&(addr->sin_addr), ip, sizeof(ip));
	printf("%s (%s) ", ip, ip);
}

void	display_response(t_env *e, int ttl)
{
	struct sockaddr_in		*sock_tmp;

	sock_tmp = NULL;
	printf("%2d ", ttl);
	for (int i = 0; i < 3; i++)
	{
		if (e->result[i].res != 0.0)
		{
			printf(" ");
			if (!is_same_host(sock_tmp, (struct sockaddr_in*)&e->result[i].addr))
			{
				sock_tmp = (struct sockaddr_in*)&e->result[i].addr;
				display_address(sock_tmp);
			}
			else
			{

			}
			printf(" %.3lf ms", e->result[i].res);
		}
		else
		{
			printf(" *");
		}
	}
	printf("\n");
}
