/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amathias </var/spool/mail/amathias>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 10:21:03 by amathias          #+#    #+#             */
/*   Updated: 2017/11/13 14:37:01 by amathias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_help()
{
	fprintf(stderr, "./ft_traceroute <destination>\n"
					"Flags:\n"
					"  -h: print help\n"
					"  -m max_ttl: max ttl\n"
					"  -f first_ttl: first ttl\n"
					"  -n: numeric mode\n"
					"  -I: use ICMP probes\n"
					);
	exit(0);
}

void	get_number(int *flag, int index, char *arg, char **argv)
{
	if (arg[1] == '\0' && argv[index + 1] != NULL)
	{
		*flag = ft_atoi(argv[index + 1]);
	}
	else
	{
		fprintf(stderr, "flag -%c need a numeric\n", *arg);
		exit(0);
	}
}

void	get_opt(t_env *e, int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc) {
		int next = 0;
		switch (argv[i][0]) {
			case '-':
				while (*++argv[i])
				{
					switch (*argv[i]) {
						case 'h' : print_help(); break;
						case 'm' : get_number(&e->flag.max_hop,
										i, argv[i], argv);
								   next = 1;
								   break;
						case 'f' : get_number(&e->flag.start_ttl,
										i, argv[i], argv);
								   next = 1;
								   break;
						case 'n' : e->flag.numeric_mode = 1;
								   break;
						case 'I' : e->flag.icmp_mode = 1;
								   break;
						default :
							printf ("Bad switch %c, ignored.\n",*argv[i]);
					}
					if (next)
						break;
				}
				if (next)
					i++;
				break;
			default:
				e->hostname = ft_strdup(argv[i]);
		}
	}
	if (e->hostname == NULL)
	{
		print_help();
		exit(1);
	}
	if (e->flag.max_hop < 0 || e->flag.max_hop > 255)
	{
		fprintf(stderr, "Invalid parameter -h, expected interger between 0 and 255\n");
		exit(1);
	}
	if (e->flag.start_ttl < 0 || e->flag.start_ttl > 255)
	{
		fprintf(stderr, "Invalid parameter -f, expected interger between 0 and 255\n");
		exit(1);
	}

}
