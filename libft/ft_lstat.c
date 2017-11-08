/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 15:44:44 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 16:41:30 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstat(t_list *begin, int index)
{
	t_list	*list;
	int		i;

	i = 0;
	list = begin;
	if (list)
	{
		while (list)
		{
			if (i == index)
				return (list);
			i++;
			list = list->next;
		}
	}
	return (NULL);
}
