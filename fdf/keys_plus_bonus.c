/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_plus_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:13:39 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:07:30 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plus_key(t_fdf *fdf)
{
	if ((*fdf).zoom == 13)
		return ;
	(*fdf).redraw = 1;
	(*fdf).zoom++;
}

void	plus_pitch(t_fdf *fdf)
{
	if ((*fdf).x_angle >= 6.3)
		(*fdf).x_angle = 0.0;
	else
		(*fdf).x_angle += 0.1;
	(*fdf).redraw = 1;
	(*fdf).rotate = 1;
}

void	plus_yaw(t_fdf *fdf)
{
	if ((*fdf).y_angle >= 6.3)
		(*fdf).y_angle = 0.0;
	else
		(*fdf).y_angle += 0.1;
	(*fdf).redraw = 1;
	(*fdf).rotate = 2;
}

void	plus_roll(t_fdf *fdf)
{
	if ((*fdf).z_angle >= 6.3)
		(*fdf).z_angle = 0.0;
	else
		(*fdf).z_angle += 0.1;
	(*fdf).redraw = 1;
	(*fdf).rotate = 3;
}
