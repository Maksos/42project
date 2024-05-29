/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:08:18 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:06:14 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(float *x, float *y, int z)
{
	float	dx;
	float	dy;

	dx = *x;
	dy = *y;
	*x = (dx - dy) * cos(0.816);
	*y = (dx + dy) * sin(0.816) - z;
}

void	parallele(float *x, float *y, int z)
{
	float	dx;
	float	dy;

	dx = *x;
	dy = *y;
	*x = (dx - dy) * cos(0.666);
	*y = (dx + dy) * sin(0.666) - z;
}

void	conique(float *x, float *y, int z)
{
	float	dx;
	float	dy;

	dx = *x;
	dy = *y;
	*x = (dx - dy) * cos(1);
	*y = (dx + dy) * sin(1) - z;
}

float	absolu(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	max_absolu(float a, float b)
{
	a = absolu(a);
	b = absolu(b);
	if (a < b)
		return (b);
	return (a);
}
