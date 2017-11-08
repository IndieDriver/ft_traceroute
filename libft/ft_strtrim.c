/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:27:58 by amathias          #+#    #+#             */
/*   Updated: 2015/12/02 16:27:43 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_blank(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*tmp;
	int		start;
	int		len;

	start = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (s[start] && ft_blank(s[start]))
		start++;
	while (len > 0 && ft_blank(s[len - 1]))
		len--;
	if (-start == len - start)
		return (ft_strnew(1));
	tmp = ft_strsub(s, start, len - start);
	return (tmp);
}
