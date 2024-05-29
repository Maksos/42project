/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:09:04 by mastie            #+#    #+#             */
/*   Updated: 2022/01/25 17:11:13 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

static char	*get_nbr(unsigned int nbr, int n, int size)
{
	char	*ret;

	if (n < 0)
		ret = malloc(sizeof(char) * (size-- + 2));
	else
		ret = malloc(sizeof(char) * (size-- + 1));
	if (ret == NULL)
		return (NULL);
	if (n < 0)
	{
		ret[size + 2] = '\0';
		ret[0] = '-';
	}
	else
		ret[size + 1] = '\0';
	while (size >= 0)
	{
		if (n < 0)
			ret[size + 1] = (nbr % 10) + 48;
		else
			ret[size] = (nbr % 10) + 48;
		size--;
		nbr = nbr / 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				i;

	i = 0;
	nbr = n;
	if (n < 0)
		nbr = -n;
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
		if (nbr == 0)
			break ;
	}
	nbr = n;
	if (n < 0)
		nbr = -n;
	if (nbr == 0)
		i = 1;
	return (get_nbr(nbr, n, i));
}
