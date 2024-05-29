/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:48:24 by mastie            #+#    #+#             */
/*   Updated: 2021/12/14 16:24:43 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_atoi_nbr(const char *str, int i, int n)
{
	long int	nbr;
	int			ret;

	nbr = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (nbr == 0)
			nbr = str[i] - 48;
		else
			nbr = nbr * 10 + str[i] - 48;
		i++;
	}
	ret = nbr * n;
	if (ret != (nbr * n))
		return (0);
	else
		return (ret);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			n++;
		i++;
	}
	n = n % 2;
	if (n == 0)
		n = 1;
	else
		n = -1;
	return (ft_atoi_nbr(str, i, n));
}
