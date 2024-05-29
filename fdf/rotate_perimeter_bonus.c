/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_perimeter_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:49:39 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:08:44 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_fdf *fdf, t_point *a, t_point *b)
{
	(*fdf).rotate = 3;
	(*fdf).z_angle = -6.3;
	while ((*fdf).z_angle < 7)
	{
		(*fdf).z_angle += 0.1;
		rotate(a, b, fdf);
	}
	(*fdf).z_angle = 0.1;
}

void	rotate_y(t_fdf *fdf, t_point *a, t_point *b)
{
	(*fdf).rotate = 2;
	(*fdf).y_angle = -6.3;
	while ((*fdf).y_angle < 7)
	{
		(*fdf).y_angle += 0.1;
		rotate(a, b, fdf);
	}
	(*fdf).y_angle = 0.1;
}

void	rotate_x(t_fdf *fdf, t_point *a, t_point *b)
{
	(*fdf).rotate = 1;
	(*fdf).x_angle = -6.3;
	while ((*fdf).x_angle < 7.0)
	{
		(*fdf).x_angle += 0.1;
		rotate(a, b, fdf);
	}
	(*fdf).x_angle = 0.1;
}

void	set_for_rotate_2(t_fdf *fdf)
{
	t_point	a;
	t_point	b;

	a = (*fdf).pmap[(*fdf).y_limit -1][0];
	b = (*fdf).pmap[0][(*fdf).x_limit -1];
	zoomed(&a, &b, fdf);
	isometric(&a.dx, &a.dy, a.z);
	isometric(&b.dx, &b.dy, b.z);
	rotate_x(fdf, &a, &b);
	rotate_y(fdf, &a, &b);
	rotate_z(fdf, &a, &b);
	a = (*fdf).pmap[0][0];
	b = (*fdf).pmap[(*fdf).y_limit - 1][(*fdf).x_limit - 1];
	zoomed(&a, &b, fdf);
	isometric(&a.dx, &a.dy, a.z);
	isometric(&b.dx, &b.dy, b.z);
	rotate_x(fdf, &a, &b);
	rotate_y(fdf, &a, &b);
	rotate_z(fdf, &a, &b);
}

void	set_for_rotate(t_fdf *fdf)
{
	t_point	a;
	t_point	b;

	a = (*fdf).pmap[(*fdf).y_limit -1][0];
	b = (*fdf).pmap[0][(*fdf).x_limit -1];
	zoomed(&a, &b, fdf);
	conique(&a.dx, &a.dy, a.z);
	conique(&b.dx, &b.dy, b.z);
	rotate_x(fdf, &a, &b);
	rotate_y(fdf, &a, &b);
	rotate_z(fdf, &a, &b);
	a = (*fdf).pmap[0][0];
	b = (*fdf).pmap[(*fdf).y_limit - 1][(*fdf).x_limit - 1];
	zoomed(&a, &b, fdf);
	conique(&a.dx, &a.dy, a.z);
	conique(&b.dx, &b.dy, b.z);
	rotate_x(fdf, &a, &b);
	rotate_y(fdf, &a, &b);
	rotate_z(fdf, &a, &b);
	set_for_rotate_2(fdf);
}
