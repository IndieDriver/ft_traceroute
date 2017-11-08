/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 20:02:22 by amathias          #+#    #+#             */
/*   Updated: 2017/11/08 20:14:18 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

uint16_t	checksum(uint16_t *data, int length)
{
	uint32_t sum = 0;

	while (length > 1) {
		sum += *data++;
		length -= 2;
	}
	if (length > 0)
		sum += * (unsigned char *) data;
	while (sum>>16)
		sum = (sum & 0xffff) + (sum >> 16);
	return((uint16_t)(~sum));
}
