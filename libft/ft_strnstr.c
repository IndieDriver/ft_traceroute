/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:06:13 by amathias          #+#    #+#             */
/*   Updated: 2015/11/27 14:59:18 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ismatch(const char *s1, const char *s2, size_t ad, size_t n)
{
	size_t count;

	count = 0;
	while (s2[count])
	{
		if (ad + count >= n)
			return (0);
		if (s1[count] != s2[count])
			return (0);
		if (s1[count] == '\0')
			return (0);
		count++;
	}
	return (1);
}

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int count;

	count = 0;
	if (ft_strlen(s2) == 0)
		return ((char*)s1);
	while (s1[count] && (size_t)count < n)
	{
		if (s1[count] == s2[0])
		{
			if (ismatch(&s1[count], s2, count, n))
				return ((char*)&s1[count]);
		}
		count++;
	}
	return (NULL);
}
