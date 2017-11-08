/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 17:32:03 by amathias          #+#    #+#             */
/*   Updated: 2017/11/08 20:15:19 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_traceroute.h"

int		x_int(int err, int res, char *str, char *file)
{
	if (res == err)
	{
		printf("%s error(%s): %s\n", str, file, strerror(errno));
		exit(1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file)
{
	if (res == err)
	{
		printf("%s error(%s): %s\n", str, file, strerror(errno));
		exit(1);
	}
	return (res);
}

void hexdump(void *mem, unsigned int len)
{
	unsigned int i, j;

	for(i = 0; i < len + ((len % 8) ? (8 - len % 8) : 0); i++)
	{
		if(i % 8 == 0)
			printf("0x%06x: ", i);
		if(i < len)
			printf("%02x ", 0xFF & ((char*)mem)[i]);
		else
			printf("   ");
		if(i % 8 == (8 - 1))
		{
			for(j = i - (8 - 1); j <= i; j++)
			{
				if(j >= len)
					putchar(' ');
				else if(ft_isprint(((char*)mem)[j]))
					putchar(0xFF & ((char*)mem)[j]);
				else /* other char */
					putchar('.');
			}
			putchar('\n');
		}
	}
}
