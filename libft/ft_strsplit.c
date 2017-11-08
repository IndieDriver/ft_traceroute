/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 19:36:01 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 11:59:38 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s == c)
			{
				if (*s == '\0')
					break ;
				s++;
			}
		}
		count++;
		while (*s != c && *s)
			s++;
		if (*s)
			s++;
	}
	return (count);
}

static int	ft_wlen(char const *s, char c)
{
	int count;

	count = 0;
	while (s[count] != c && s[count])
	{
		count++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	if ((tab = (char**)malloc(sizeof(char*) * ft_countword(s, c) + 1)) == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		if (!ft_wlen(s, c))
			tab[index] = NULL;
		else
			tab[index] = ft_strsub(s, 0, ft_wlen(s, c));
		while (*s != c && *s)
			s++;
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
