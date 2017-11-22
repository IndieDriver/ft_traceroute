/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:44:37 by amathias          #+#    #+#             */
/*   Updated: 2017/11/22 08:58:41 by amathias         ###   ########.fr       */
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

void	display_address(int numeric_mode, struct sockaddr_in *addr)
{
	char ip[INET_ADDRSTRLEN];

	inet_ntop(addr->sin_family,
			&(addr->sin_addr), ip, sizeof(ip));
	if (numeric_mode)
		printf("%s ", ip);
	else
		printf("%s (%s) ", ip, ip);
}

int		count_digits(int value)
{
	int res;

	res = 0;
	while (value != 0)
	{
		value /= 10;
		res++;
	}
	return (res);
}

void	display_response(t_env *e, int ttl)
{
	struct sockaddr_in		*sock_tmp;

	sock_tmp = NULL;
	printf("%*d ", count_digits(e->flag.max_hop), ttl);
	for (int i = 0; i < 3; i++)
	{
		if (e->result[i].res != 0.0)
		{
			printf(" ");
			if (!is_same_host(sock_tmp, (struct sockaddr_in*)&e->result[i].addr))
			{
				sock_tmp = (struct sockaddr_in*)&e->result[i].addr;
				display_address(e->flag.numeric_mode, sock_tmp);
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
