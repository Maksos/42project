/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_views_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:14:20 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:07:46 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_flat(t_fdf *fdf)
{
	(*fdf).redraw = 1;
	(*fdf).view = 0;
}

void	isometric_view(t_fdf *fdf)
{
	(*fdf).redraw = 1;
	(*fdf).view = 1;
}

void	conique_view(t_fdf *fdf)
{
	(*fdf).redraw = 1;
	(*fdf).view = 3;
}

void	parallele_view(t_fdf *fdf)
{
	(*fdf).redraw = 1;
	(*fdf).view = 2;
}
