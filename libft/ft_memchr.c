/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:33:10 by amathias          #+#    #+#             */
/*   Updated: 2015/11/26 18:45:45 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*sptr;
	size_t	i;

	i = 0;
	sptr = (char*)s;
	while (i < n)
	{
		if (sptr[i] == (char)c)
			return (&sptr[i]);
		i++;
	}
	return (NULL);
}
