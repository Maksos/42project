/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:37:02 by mastie            #+#    #+#             */
/*   Updated: 2022/03/11 19:39:28 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str && str[i])
// 		i++;
// 	return (i);
// }

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

t_data	*get_char(t_data *data)
{
	char	c;

	c = va_arg(data->ap, int);
	data->ret += write(1, &c, 1);
	return (data);
}

t_data	*get_string(t_data *data)
{
	char	*s;
	int		len;

	s = va_arg(data->ap, char *);
	if (s == NULL)
	{
		ft_putstr("(null)");
		data->ret += 6;
	}
	else
	{
		len = ft_strlen(s);
		ft_putstr(s);
		data->ret += len;
	}
	return (data);
}

t_data	*get_integer(t_data *data)
{
	int	integer;
	int	len;

	integer = va_arg(data->ap, int);
	data->r_arg = ft_itoa(integer);
	len = ft_strlen(data->r_arg);
	data->ret += len;
	if (data->r_arg)
	{
		ft_putstr(data->r_arg);
		free(data->r_arg);
	}
	return (data);
}
