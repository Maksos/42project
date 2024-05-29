/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:37:38 by mastie            #+#    #+#             */
/*   Updated: 2022/03/11 20:07:58 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_data	*init_data(t_data *data)
{
	if (data == NULL)
		data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->r_arg = NULL;
	data->ret = 0;
	return (data);
}

t_data	*arg_type(t_data *data, const char **fmt)
{
	if (**fmt == 'c')
		data = get_char(data);
	else if (**fmt == 's')
		data = get_string(data);
	else if (**fmt == 'p')
		data = get_uintptr(data);
	else if (**fmt == 'd' || **fmt == 'i')
		data = get_integer(data);
	else if (**fmt == 'u')
		data = get_uint(data);
	else if (**fmt == 'x')
		data = get_lower_hexadecimal(data);
	else if (**fmt == 'X')
		data = get_upper_hexadecimal(data);
	else if (**fmt == '%')
		data = get_percentil(data);
	return (data);
}

t_data	*get_data(t_data *data, const char **fmt)
{
	data = arg_type(data, fmt);
	return (data);
}

int	ft_printf(const char *fmt, ...)
{
	t_data	*data;
	int		ret;

	data = NULL;
	data = init_data(data);
	if (data == NULL)
		return (0);
	va_start(data->ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			data = get_data(data, &fmt);
		}
		else
			data->ret += write(1, &*fmt, 1);
		if (*fmt)
			fmt++;
	}
	va_end(data->ap);
	ret = data->ret;
	free(data);
	return (ret);
}
