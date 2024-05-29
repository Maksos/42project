/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:34:42 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:08:56 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z_axe_rotation(float *x, float *y, t_fdf *fdf, float angle)
{
	float	dx;
	float	dy;
	float	abs;

	dx = *x;
	dy = *y;
	*x = cos(angle) * dx + sin(angle) * dy;
	*y = -sin(angle) * dx + cos(angle) * dy;
	if (*y < 0)
	{
		abs = -(*y);
		if ((*fdf).y_draw < abs)
			(*fdf).y_draw = abs + 1;
	}
	if (*x < 0)
	{
		abs = -(*x);
		if ((*fdf).x_draw < abs)
			(*fdf).x_draw = abs + 1;
	}
}

void	y_axe_rotation(float *x, t_fdf *fdf, float *z, float angle)
{
	float	dx;
	float	dz;
	float	abs;

	dx = *x;
	dz = *z;
	*x = cos(angle) * dx + sin(angle) * dz;
	*z = cos(angle) * dx + -sin(angle) * dz;
	if (*x < 0)
	{
		abs = -(*x);
		if ((*fdf).x_draw < abs)
			(*fdf).x_draw = abs + 1;
	}
	if (*z < 0)
	{
		abs = -(*z);
		if ((*fdf).z_draw < abs)
			(*fdf).z_draw = abs + 1;
	}
}

void	x_axe_rotation(t_fdf *fdf, float *y, float *z, float angle)
{
	float	dy;
	float	dz;
	float	abs;

	dy = *y;
	dz = *z;
	*y = cos(angle) * dy + -sin(angle) * dz;
	*z = sin(angle) * dy + cos(angle) * dz;
	if (*z < 0)
	{
		abs = -(*z);
		if ((*fdf).z_draw < abs)
			(*fdf).z_draw = abs + 1;
	}
	if (*y < 0)
	{
		abs = -(*y);
		if ((*fdf).y_draw < abs)
			(*fdf).y_draw = abs + 1;
	}
}

void	rotate(t_point *from, t_point *to, t_fdf *fdf)
{
	if ((*fdf).rotate == 1)
	{
		x_axe_rotation(fdf, &(*from).dy, &(*from).dz, (*fdf).x_angle);
		x_axe_rotation(fdf, &(*to).dy, &(*to).dz, (*fdf).x_angle);
	}
	if ((*fdf).rotate == 2)
	{
		y_axe_rotation(&(*from).dx, fdf, &(*from).dz, (*fdf).y_angle);
		y_axe_rotation(&(*to).dx, fdf, &(*to).dz, (*fdf).y_angle);
	}
	if ((*fdf).rotate == 3)
	{
		z_axe_rotation(&(*from).dx, &(*from).dy, fdf, (*fdf).z_angle);
		z_axe_rotation(&(*to).dx, &(*to).dy, fdf, (*fdf).z_angle);
	}
}
