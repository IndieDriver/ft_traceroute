/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:44:37 by amathias          #+#    #+#             */
/*   Updated: 2017/11/09 12:37:41 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	display_header_info(t_env *e)
{
	char ip[INET_ADDRSTRLEN];

	inet_ntop(e->addr->ai_family,
			&((struct sockaddr_in *)e->addr->ai_addr)->sin_addr, ip, sizeof(ip));

	printf("traceroute to %s (%s), %lu(%lu) bytes of data.\n", e->hostname, ip,
			sizeof(t_rpacket) - sizeof(struct icmp), sizeof(t_rpacket));
}

void	display_response(t_env *e, int ttl, struct sockaddr_in *addr)
{
	char ip[INET_ADDRSTRLEN];

	(void)e;
	if (addr != NULL)
	{
		inet_ntop(addr->sin_family,
				&(addr->sin_addr), ip, sizeof(ip));
		printf("%d %s (%s)\n", ttl, ip, ip);
	}
	else
	{
		printf("%d * * *\n", ttl);
	}
}
