/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:13:11 by amathias          #+#    #+#             */
/*   Updated: 2015/11/26 16:55:55 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *destptr;
	char *srcptr;

	destptr = dest;
	srcptr = (char*)src;
	while (n > 0)
	{
		*destptr++ = *srcptr++;
		n--;
	}
	return (dest);
}
