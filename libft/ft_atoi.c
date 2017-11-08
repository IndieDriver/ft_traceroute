/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:55:21 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 16:07:53 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_isvalid(int c)
{
	if (ft_isspace(c) || ft_isdigit(c) || c == '-'
			|| c == '+')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int sum;
	int sign;

	sum = 0;
	while ((sign = 0) && ft_isspace(*str))
		str++;
	while (*str && ft_isvalid(*str))
	{
		if (*str == '-' && sign == 0)
			sign = -1;
		else if (((*str) == '+' && sign == 0)
				|| (ft_isdigit(*str) && sign == 0))
			sign = 1;
		else if ((*str == '-' && sign != 0) || (*str == '+' && sign != 0) ||
				(ft_isspace(*str) && sign != 0))
			break ;
		if (ft_isdigit(*str))
			sum = (*str - '0') + (sum * 10);
		else if (!ft_isdigit(*str) && sum != 0)
			return (sum);
		str++;
	}
	if (sign == -1)
		sum = -sum;
	return (sum);
}
