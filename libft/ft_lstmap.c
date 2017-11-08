/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:47:36 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 15:52:39 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_new;

	if (!lst || !f)
		return (NULL);
	if ((lst_new = (t_list*)malloc(sizeof(lst) + 1)))
	{
		lst_new = f(lst);
		if (lst->next)
			lst_new->next = ft_lstmap(lst->next, *f);
	}
	else
		return (NULL);
	return (lst_new);
}
