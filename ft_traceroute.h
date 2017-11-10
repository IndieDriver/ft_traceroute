/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 16:50:28 by amathias          #+#    #+#             */
/*   Updated: 2017/11/10 09:45:54 by amathias         ###   ########.fr       */
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

typedef	struct				s_result
{
	int						has_completed;
	double					res;
	struct sockaddr_storage	addr;
	struct timeval			send_time;
}							t_result;

typedef struct				s_env
{
	char					*hostname;
	char					*ip;
	int						socket;
	struct addrinfo			*addr;
	struct {
		int					help;
		int					max_hop;
	}	flag;
	int						has_timeout;
	int						sent;
	int						received;
	struct timeval			start_time;
	t_result				result[3];
	int						end;
}							t_env;

typedef struct				s_packet
{
	struct icmp				icmp;
	uint8_t					data[38];
}							t_packet;

typedef struct				s_rpacket
{
	struct iphdr			ipheader;
	struct icmp				icmp;
	uint8_t					data[38];
}							t_rpacket;

t_env						g_env;

uint16_t					checksum(uint16_t *data, int length);

int							x_int(int err, int res, char *str, char *file);
void						*x_void(void *err, void *res, char *str, char *file);
void						hexdump(void *mem, unsigned int len);

void						get_opt(t_env *e, int argc, char **argv);

void						display_header_info(t_env *env);
void						display_response(t_env *e, int ttl);

void						ft_sleep(uint32_t sec);
uint16_t					swap_byte16_t(uint16_t val);
double						get_time_elapsed(struct timeval *t1,
								struct timeval *t2);
int							is_same_host(struct sockaddr_in *addr1,
								struct sockaddr_in *addr2);
int							has_results(t_env *e);

void						sig_handler(int sig);

#endif
