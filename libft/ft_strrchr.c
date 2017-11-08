/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:30:55 by amathias          #+#    #+#             */
/*   Updated: 2015/11/27 11:04:57 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			tmp = (char*)&str[i];
		i++;
	}
	if (str[i] == c)
		return ((char*)&str[i]);
	return (tmp);
}
