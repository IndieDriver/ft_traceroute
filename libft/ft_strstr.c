/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:48:10 by amathias          #+#    #+#             */
/*   Updated: 2015/11/27 14:59:40 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_containsubstring(const char *s1, const char *s2, int i, int j)
{
	while (s2[j])
	{
		if (s1[i + j] != s2[j])
			return (0);
		j++;
	}
	return (1);
}

char		*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		return (NULL);
	while (s1[i])
	{
		if (s1[i] == s2[j])
		{
			if (ft_containsubstring(s1, s2, i, j))
				return ((char*)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
