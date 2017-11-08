/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:50:28 by amathias          #+#    #+#             */
/*   Updated: 2017/11/08 20:32:55 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>
# include <stdlib.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>

# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>
# include <math.h>

# include "libft/libft.h"

# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))
# define XV(err,res,str) (x_void(err,res,str,__FILE__))
# define X(err,res,str) (x_int(err,res,str,__FILE__))

typedef struct				s_env
{
	char					*hostname;
	char					*ip;
	int						socket;
	struct addrinfo			*addr;
	struct {
		int					help;
	}	flag;
	int						has_timeout;
	int						sent;
	int						received;
	struct timeval			start_time;
	double					ping_min;
	double					ping_max;
	double					sum;
	double					sum_square;
}							t_env;

typedef struct				s_packet
{
	struct icmp				icmp;
	uint8_t					data[36];
}							t_packet;

typedef struct				s_rpacket
{
	struct iphdr			ipheader;
	struct icmp				icmp;
	uint8_t					data[36];
}							t_rpacket;

t_env						g_env;

uint16_t					checksum(uint16_t *data, int length);

int							x_int(int err, int res, char *str, char *file);
void						*x_void(void *err, void *res, char *str, char *file);
void						hexdump(void *mem, unsigned int len);

void						get_opt(t_env *e, int argc, char **argv);

void						display_header_info(t_env *env);
void						display_response(t_env *e, int bytes_receive,
								int seq, double duration);

void						ft_sleep(uint32_t sec);
uint16_t					swap_byte16_t(uint16_t val);
double						get_time_elapsed(struct timeval *t1,
								struct timeval *t2);

void						sig_handler(int sig);

#endif
