/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:36:19 by mastie            #+#    #+#             */
/*   Updated: 2022/10/27 19:27:33 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ultoa(unsigned int nbr, char a, int len)
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
		i = nbr % 16;
		if (i >= 0 && i <= 9)
			ret[len] = i + 48;
		else
			ret[len] = i + ((int)a - 10);
		len--;
		nbr = nbr / 16;
	}
	return (ret);
}	

t_data	*get_lower_hexadecimal(t_data *data)
{
	unsigned int		glh;
	int					len;

	glh = va_arg(data->ap, unsigned long long int);
	len = nbr_len(glh, 16);
	data->ret += len;
	data->r_arg = ultoa(glh, 'a', len);
	if (data->r_arg)
	{
		ft_putstr(data->r_arg);
		free(data->r_arg);
	}
	return (data);
}

t_data	*get_upper_hexadecimal(t_data *data)
{
	unsigned int	guh;
	int				len;

	guh = va_arg(data->ap, unsigned long long int);
	len = nbr_len(guh, 16);
	data->ret += len;
	data->r_arg = ultoa(guh, 'A', len);
	if (data->r_arg)
	{
		ft_putstr(data->r_arg);
		free(data->r_arg);
	}
	return (data);
}
