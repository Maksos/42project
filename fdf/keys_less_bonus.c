/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_less_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:14:00 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:07:19 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	less_key(t_fdf *fdf)
{
	if ((*fdf).zoom == 5)
		return ;
	(*fdf).zoom--;
	(*fdf).redraw = 1;
}

void	less_pitch(t_fdf *fdf)
{
	if ((*fdf).x_angle <= 0.0)
		(*fdf).x_angle = 6.3;
	else
		(*fdf).x_angle -= 0.1;
	(*fdf).redraw = 1;
	(*fdf).rotate = 1;
}

void	less_yaw(t_fdf *fdf)
{
	if ((*fdf).y_angle <= 0.0)
		(*fdf).y_angle = 6.3;
	else
		(*fdf).y_angle -= 0.1;
	(*fdf).redraw = 1;
	(*fdf).rotate = 2;
}

void	less_roll(t_fdf *fdf)
{
	if ((*fdf).z_angle <= 0.0)
		(*fdf).z_angle = 6.3;
	else
		(*fdf).z_angle -= 0.1;
	(*fdf).redraw = 1;
	(*fdf).rotate = 3;
}
