/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:56:08 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:09:05 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_point *point, int zoom)
{
	(*point).dx = (*point).x * zoom;
	(*point).dy = (*point).y * zoom;
	(*point).dz = (*point).z * zoom;
}

void	zoomed(t_point *a, t_point *b, t_fdf *fdf)
{
	(*a).dx = (*a).x * 13;
	(*b).dx = (*b).x * 13;
	(*a).dy = (*a).y * 13;
	(*b).dy = (*b).y * 13;
	(*a).dz = (*fdf).z_limit * 13;
	(*b).dz = (*fdf).z_limit * 13;
}

void	colored(t_point a, t_point b, t_fdf *fdf)
{
	if ((*fdf).colored == 1)
		(*fdf).color = a.color;
	else
	{
		if ((a.color == 16777215 || b.color == 16777215)
			&& (a.z != 0 || b.z != 0))
			(*fdf).color = 255;
		else
			(*fdf).color = a.color;
	}
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == c)
			return (0);
		i++;
	}
	return (-1);
}

void	position_to_draw(t_fdf *fdf)
{
	if ((*fdf).view == 4)
	{
		set_for_rotate(fdf);
		(*fdf).view = 0;
		(*fdf).rotate = 1;
		ft_printf("x_draw [%d] y_draw [%d] z_draw[%d] zoom [%d]\n",
			(*fdf).x_draw, (*fdf).y_draw, (*fdf).z_draw, (*fdf).zoom);
		(*fdf).img_width = (*fdf).x_draw + (*fdf).z_draw
			+ ((*fdf).z_limit * (*fdf).zoom);
		(*fdf).img_height = (*fdf).y_draw + (*fdf).z_draw
			+ ((*fdf).z_limit * (*fdf).zoom);
		ft_printf("width = [%d] height = [%d]\n",
			(*fdf).img_width, (*fdf).img_height);
	}
}
