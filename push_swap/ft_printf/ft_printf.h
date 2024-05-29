/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:50 by mastie            #+#    #+#             */
/*   Updated: 2022/10/27 19:27:42 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_data
{
	va_list	ap;
	va_list	cpy;
	int		ret;
	char	*r_arg;
}		t_data;

//int		ft_strlen(const char *str);
int		ft_printf(const char *fmt, ...);
int		nbr_len(unsigned int nbr, int base);
void	ft_putstr(char *str);
//void	ft_putnbr_fd(int n, int fd);
//char	*ft_itoa(int n);
t_data	*print_by_flags(t_data *data, int len);
t_data	*get_char(t_data *data);
t_data	*get_string(t_data *data);
t_data	*get_uintptr(t_data *data);
t_data	*get_integer(t_data *data);
t_data	*get_uint(t_data *data);
t_data	*get_lower_hexadecimal(t_data *data);
t_data	*get_upper_hexadecimal(t_data *data);
t_data	*get_percentil(t_data *data);

#endif
