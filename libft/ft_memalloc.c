/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:03:54 by amathias          #+#    #+#             */
/*   Updated: 2015/11/30 16:19:09 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *tmp;

	if (size == 0)
		return (NULL);
	tmp = malloc(size);
	if (tmp == NULL)
		return (NULL);
	tmp = ft_memset(tmp, 0, size);
	return (tmp);
}
