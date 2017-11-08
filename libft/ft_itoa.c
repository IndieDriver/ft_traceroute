/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 17:11:09 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 17:35:07 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int i;

	i = 1;
	if (n < 0)
		i++;
	while (n > 9 || n < -9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*tmp;
	int		ntmp;
	int		neg;
	int		i;

	i = 0;
	neg = 0;
	if (n < 0)
		neg = 1;
	if ((tmp = malloc(sizeof(char) * ft_intlen(n) + 1)) == NULL)
		return (NULL);
	if (n == 0)
		tmp[i++] = '0';
	while (n != 0)
	{
		ntmp = ABS((n % 10));
		tmp[i++] = '0' + ntmp;
		n = n / 10;
	}
	if (neg)
		tmp[i++] = '-';
	tmp[i] = '\0';
	return (ft_strrev(tmp));
}
