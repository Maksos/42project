/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_arrows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:15:26 by mastie            #+#    #+#             */
/*   Updated: 2022/11/30 22:23:50 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	left_arrow(t_fdf *fdf)
{
	(*fdf).x_shift -= 500;
	(*fdf).repos = 1;
}

void	up_arrow(t_fdf *fdf)
{
	(*fdf).y_shift -= 500;
	(*fdf).repos = 1;
}

void	right_arrow(t_fdf *fdf)
{
	(*fdf).x_shift += 500;
	(*fdf).repos = 1;
}

void	down_arrow(t_fdf *fdf)
{
	(*fdf).y_shift += 500;
	(*fdf).repos = 1;
}

void	ctrl_cancel(t_fdf *fdf)
{
	mlx_clear_window((*fdf).mlx, (*fdf).win);
	mlx_destroy_window((*fdf).mlx, (*fdf).win);
	mlx_destroy_image((*fdf).mlx, (*fdf).img.img);
	mlx_destroy_display((*fdf).mlx);
	free((*fdf).mlx);
	free_map(fdf);
	exit(EXIT_SUCCESS);
}
