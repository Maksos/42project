/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:36:02 by mastie            #+#    #+#             */
/*   Updated: 2022/07/20 14:14:11 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	nbr_len(unsigned int nbr, int base)
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

char	*uinttoa(unsigned int uint, int len)
{
	char	*ret;
	int		i;

	ret = NULL;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ret[len--] = '\0';
	while (len >= 0)
	{
		i = uint % 10;
		ret[len] = i + 48;
		len--;
		uint = uint / 10;
	}
	return (ret);
}

t_data	*get_uint(t_data *data)
{
	unsigned int	ul;
	int				len;

	ul = va_arg(data->ap, unsigned int);
	len = nbr_len(ul, 10);
	data->ret += len;
	data->r_arg = uinttoa(ul, len);
	if (data->r_arg)
	{
		ft_putstr(data->r_arg);
		free(data->r_arg);
	}
	return (data);
}
