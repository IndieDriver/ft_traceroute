/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 17:35:35 by amathias          #+#    #+#             */
/*   Updated: 2016/02/17 12:53:17 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoinfree(char *str, char *buf, int size)
{
	char *tmp;

	tmp = NULL;
	if (str)
	{
		if ((tmp = malloc(sizeof(char) *
						(ft_strlen(str) + size + 1))) == NULL)
			return (NULL);
	}
	else
	{
		if ((tmp = malloc(sizeof(char) * size + 1)) == NULL)
			return (NULL);
	}
	tmp[0] = '\0';
	if (str)
		tmp = ft_strcpy(tmp, str);
	ft_strncat(tmp, buf, size);
	free(str);
	str = NULL;
	return (tmp);
}

int		containeof(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*shift_buf(char *buf, int start)
{
	int i;

	i = 0;
	while (buf[start])
	{
		buf[i] = buf[start];
		i++;
		start++;
	}
	buf[i] = '\0';
	return (buf);
}

int		get_next_line(int const fd, char **line)
{
	static t_buf	sbuf;
	char			*tmp;
	int				end;

	tmp = NULL;
	while (1)
	{
		if (!ft_strlen(sbuf.buf))
		{
			if ((sbuf.ret = read(fd, sbuf.buf, BUFF_SIZE)) == -1)
				return (-1);
			sbuf.buf[sbuf.ret] = '\0';
			if (!sbuf.ret && !ft_strlen(sbuf.buf))
				break ;
		}
		if (!(tmp = strjoinfree(tmp, sbuf.buf,
				containeof(sbuf.buf) != -1 ? containeof(sbuf.buf) : BUFF_SIZE)))
			return (-1);
		end = containeof(sbuf.buf) != -1 ? 1 : 0;
		shift_buf(sbuf.buf, containeof(sbuf.buf) != -1 ?
				containeof(sbuf.buf) + 1 : BUFF_SIZE);
		if (end)
			break ;
	}
	return ((*line = tmp) && (sbuf.ret != 0 || ft_strlen(tmp)));
}
