/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:40:23 by mastie            #+#    #+#             */
/*   Updated: 2022/10/22 19:15:33 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include "ft_printf/ft_printf.h"
# include <errno.h>

typedef struct s_server_data
{
	char			*str;
	int				i;
	unsigned char	c;
	int				bit;
	int				init;
	size_t			size;
	int				sized;

}		t_server_data;

typedef struct s_client_data
{
	char		*str;
	char		*size;
	int			i;
	int			bit;
	int			server_pid;

}		t_client_data;

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		input_pid(char *pid_str);
#endif
