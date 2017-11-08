/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:02:12 by amathias          #+#    #+#             */
/*   Updated: 2015/11/27 11:00:19 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	char		*tmpdest;
	const char	*tmpsrc;
	size_t		n;
	size_t		destlen;

	n = dstsize;
	tmpdest = dest;
	tmpsrc = src;
	while (n-- != 0 && *tmpdest != '\0')
		tmpdest++;
	destlen = tmpdest - dest;
	n = dstsize - destlen;
	if (n == 0)
		return (destlen + ft_strlen(tmpsrc));
	while (*tmpsrc != '\0')
	{
		if (n != 1)
		{
			*tmpdest++ = *tmpsrc;
			n--;
		}
		tmpsrc++;
	}
	*tmpdest = '\0';
	return (destlen + (tmpsrc - src));
}
