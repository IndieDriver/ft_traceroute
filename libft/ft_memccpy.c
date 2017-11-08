/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:59 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 16:53:56 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*destptr;
	char	*srcptr;
	size_t	i;

	i = 0;
	destptr = (char*)dest;
	srcptr = (char*)src;
	while (i < n)
	{
		destptr[i] = srcptr[i];
		if (srcptr[i] == c)
			return ((char*)&destptr[i] + 1);
		i++;
	}
	return (NULL);
}
