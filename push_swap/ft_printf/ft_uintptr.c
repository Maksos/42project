/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:40:40 by mastie            #+#    #+#             */
/*   Updated: 2022/02/14 16:18:56 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	uint_len(unsigned long int nbr, int base)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}

void	uintptrtoa(uintptr_t nbr)
{
	int	i;

	if (nbr / 16 != 0)
		uintptrtoa(nbr / 16);
	i = (nbr % 16);
	if (i >= 0 && i <= 9)
		i += 48;
	else
		i += 'a' - 10;
	write(1, &i, 1);
}

t_data	*get_uintptr(t_data *data)
{
	uintptr_t	ptr;
	int			len;

	ptr = va_arg(data->ap, uintptr_t);
	len = 0;
	if (ptr != 0)
	{
		len = uint_len(ptr, 16);
		data->ret += len;
		data->ret += write(1, "0x", 2);
		uintptrtoa(ptr);
	}
	else
		data->ret += write(1, "(nil)", 5);
	return (data);
}

t_data	*get_percentil(t_data *data)
{
	data->ret += write(1, "%", 1);
	return (data);
}
