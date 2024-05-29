/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_views.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:14:20 by mastie            #+#    #+#             */
/*   Updated: 2022/11/30 22:24:16 by mastie           ###   ########.fr       */
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
