/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 22:08:43 by mastie            #+#    #+#             */
/*   Updated: 2022/11/02 17:56:11 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_putnbr_base_to(int nb, char *base_to);

int	in_base(char nbr, char *base)
{
	int	i;

	i = 0;
	while (base && base[i])
	{
		if (base[i] == nbr)
			return (i);
		i++;
	}
	return (-1);
}

int	valid_base(char *base)
{
	int		i;
	int		t;

	i = 0;
	while (base && base[i])
	{
		if (base[i] == '+' || base[i] == '-'
			|| (base[i] >= 9 && base[i] <= 13) || base[i] == ' ')
			return (-1);
		if (base[i + 1] && base[i + 1] != '\0')
		{
			t = i + 1;
			while (base[t] && base[i] != base[t])
				t++;
			if (base[t] != '\0')
				return (-1);
		}
		i++;
	}
	if (i <= 1)
		return (-1);
	return (0);
}

int	nbr_base_from(char *nbr, int i, char *base_from)
{
	int	nb;
	int	lb;

	nb = 0;
	lb = 0;
	while (base_from && base_from[lb])
		lb++;
	while (nbr && nbr[i] && in_base(nbr[i], base_from) != -1)
	{
		if (nbr == 0)
			nb = in_base(nbr[i], base_from);
		else
			nb = nb * lb + in_base(nbr[i], base_from);
		i++;
	}
	return (nb);
}

int	ft_atoi_base_from(char *nbr, char *base_from)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	n = 1;
	while (nbr && nbr[i] && (nbr[i] == '\t' || nbr[i] == '\n' || nbr[i] == '\r'
			|| nbr[i] == '\v' || nbr[i] == '\f' || nbr[i] == ' '))
		i++;
	if (nbr && nbr[i] && (nbr[i] == '-' || nbr[i] == '+'))
	{
		if (nbr[i] == '-')
			n = -n;
		i++;
	}
	s = i;
	while (nbr && nbr[s] && in_base(nbr[s], base_from) != -1)
		s++;
	if (i == s)
		return (0);
	return (nbr_base_from(nbr, i, base_from) * n);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*ret;

	ret = 0;
	if (valid_base(base_from) == 0 && valid_base(base_to) == 0)
		ret = ft_putnbr_base_to(ft_atoi_base_from(nbr, base_from), base_to);
	return (ret);
}
