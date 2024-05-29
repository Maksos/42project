/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:53:34 by mastie            #+#    #+#             */
/*   Updated: 2022/11/25 05:32:46 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_put_pixel(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	view(t_point *from, t_point *to, t_fdf *fdf)
{
	if ((*fdf).view == 1)
	{
		isometric(&(*from).dx, &(*from).dy, (*from).z);
		isometric(&(*to).dx, &(*to).dy, (*to).z);
	}
	else if ((*fdf).view == 2)
	{
		parallele(&(*from).dx, &(*from).dy, (*from).z);
		parallele(&(*to).dx, &(*to).dy, (*to).z);
	}
	else if ((*fdf).view == 3)
	{
		conique(&(*from).dx, &(*from).dy, (*from).z);
		conique(&(*to).dx, &(*to).dy, (*to).z);
	}
}

void	zoom_view_rotate(t_point *from, t_point *to, t_fdf *fdf)
{
	zoom(from, (*fdf).zoom);
	zoom(to, (*fdf).zoom);
	view(from, to, fdf);
	if ((*fdf).rotate > 0)
		rotate(from, to, fdf);
}

void	bresenham(t_point from, t_point to, t_fdf *fdf)
{
	float	x_step;
	float	y_step;
	int		max;

	zoom_view_rotate(&from, &to, fdf);
	x_step = to.dx - from.dx;
	y_step = to.dy - from.dy;
	max = max_absolu(x_step, y_step);
	x_step /= max;
	y_step /= max;
	colored(from, to, fdf);
	while ((int)(from.dx - to.dx) || (int)(from.dy - to.dy))
	{
		my_mlx_put_pixel((*fdf).img, (*fdf).x_draw + from.dx,
			(*fdf).y_draw + from.dy, (*fdf).color);
		from.dx += x_step;
		from.dy += y_step;
	}
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < (*fdf).y_limit)
	{
		x = 0;
		while (x < (*fdf).x_limit)
		{
			if (x < (*fdf).x_limit - 1)
				bresenham((*fdf).pmap[y][x], (*fdf).pmap[y][x + 1], fdf);
			if (y < (*fdf).y_limit - 1)
				bresenham((*fdf).pmap[y][x], (*fdf).pmap[y + 1][x], fdf);
			x++;
		}
		y++;
	}
	(*fdf).rotate = 0;
}
