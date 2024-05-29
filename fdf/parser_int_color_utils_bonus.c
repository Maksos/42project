/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int_color_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:33:02 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:08:34 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_input_is_valid(char *color)
{
	int	i;

	i = 0;
	while (color && color[i])
	{
		if (i == 0 && color[i] != '0')
			return (-1);
		else if (i == 1 && color[i] != 'x')
			return (-1);
		if (color[i] >= 65 && color[i] <= 70)
			color[i] = ft_tolower(color[i]);
		if (i > 1 && (is_charset(color[i], "0123456789abcdef") == -1))
			return (-1);
		i++;
	}
	if (i == 2 && !color[i])
		return (-1);
	return (0);
}

int	int_input_is_valid(char *nbr)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (nbr && nbr[i])
	{
		if (nbr[i] == '-')
			n++;
		if (n > 1)
			return (-1);
		if (ft_isdigit(nbr[i]) == 0 && nbr[i] != '-')
			return (-1);
		i++;
	}
	return (0);
}
