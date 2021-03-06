/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:40:42 by amathias          #+#    #+#             */
/*   Updated: 2017/11/22 09:52:53 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

double		get_time_elapsed(struct timeval *t1, struct timeval *t2)
{
	double duration = (((double)t2->tv_sec * 1000000.0 + t2->tv_usec) -
				((double)t1->tv_sec * 1000000.0 + t1->tv_usec)) / 1000;
	return (duration);
}

uint16_t	swap_byte16_t(uint16_t val)
{
	return ((uint16_t)((val & 0xFF) << 8 | (val & 0xFF00) >> 8));
}

void		ft_sleep(uint32_t seconds)
{
	struct timeval	start;
	struct timeval	tmp;
	double			t;

	t = 1000 * (double)seconds;
	gettimeofday(&start, NULL);
	gettimeofday(&tmp, NULL);
	while (get_time_elapsed(&start, &tmp) < t)
	{
		gettimeofday(&tmp, NULL);
	}
}

void		sig_handler(int s)
{
	if (s == SIGALRM)
		g_env.has_timeout = 1;
	if (s == SIGINT)
		exit(0);
}

int			is_same_host(struct sockaddr_in *addr1, struct sockaddr_in *addr2)
{
	if (!addr1 || !addr2)
		return (0);
	if (addr1->sin_addr.s_addr == addr2->sin_addr.s_addr)
		return (1);
	return (0);
}

int			has_results(t_env *e)
{
	for (int i = 0; i < 3; i++)
	{
		if (!e->result[i].has_completed)
		{
			return (0);
		}
	}
	return (1);
}
