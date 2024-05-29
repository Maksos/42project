/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:09:08 by mastie            #+#    #+#             */
/*   Updated: 2021/08/25 20:55:37 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_base_length(char *base)
{
	int	i;

	i = 0;
	while (base && base[i])
		i++;
	return (i);
}

char	*ft_nbr_to_base(unsigned int nbr, char *base, int lb, char *ret)
{
	int				i;
	unsigned int	save;

	i = 0;
	save = nbr;
	while (save / lb)
	{
		save /= lb;
		i++;
	}
	if (ret[0] == '-')
		ret[++i] = base[nbr % lb];
	else
		ret[i] = base[nbr % lb];
	if (nbr / lb)
		ft_nbr_to_base(nbr / lb, base, lb, ret);
	return (ret);
}

int	ft_nbr_lenght(unsigned int nbr, int lb)
{
	int	i;

	i = 0;
	while (nbr / lb)
	{
		nbr /= lb;
		i++;
	}
	return (i);
}

char	*negative(char *ret)
{
	int		i;
	char	*neg;

	i = 0;
	while (ret && ret[i])
		i++;
	neg = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (ret && ret[i])
	{
		if (i == 0)
			neg[i] = '-';
		neg[i + 1] = ret[i];
		i++;
	}
	neg[i + 1] = 0;
	free(ret);
	return (neg);
}

char	*ft_putnbr_base_to(int nb, char *base)
{
	int				lb;
	unsigned int	nbr;
	char			*ret;
	int				i;

	lb = ft_base_length(base);
	nbr = nb;
	i = 0;
	if (nb < 0)
		nbr = -nb;
	i = ft_nbr_lenght(nbr, lb) + 2;
	ret = malloc(sizeof(char) * i);
	while (--i >= 0)
		ret[i] = 0;
	ret = ft_nbr_to_base(nbr, base, lb, ret);
	if (nb < 0)
		return (negative(ret));
	return (ret);
}
