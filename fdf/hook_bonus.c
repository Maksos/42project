/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:03:55 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:06:52 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exposure(t_fdf *fdf)
{
	mlx_destroy_window((*fdf).mlx, (*fdf).win);
	mlx_destroy_image((*fdf).mlx, (*fdf).img.img);
	mlx_destroy_display((*fdf).mlx);
	free((*fdf).mlx);
	free_map(fdf);
	exit(EXIT_SUCCESS);
	return (0);
}

int	arrows(int keysym, t_fdf *fdf)
{
	if (keysym == 65361)
		left_arrow(fdf);
	if (keysym == 65362)
		up_arrow(fdf);
	if (keysym == 65363)
		right_arrow(fdf);
	if (keysym == 65364)
		down_arrow(fdf);
	return (0);
}

int	views(int keysym, t_fdf *fdf)
{
	if (keysym == 65438)
		reset_flat(fdf);
	if (keysym == 65436)
		isometric_view(fdf);
	if (keysym == 65434)
		conique_view(fdf);
	if (keysym == 65437)
		parallele_view(fdf);
	return (0);
}

int	rotations(int keysym, t_fdf *fdf)
{
	if (keysym == 65451)
		plus_key(fdf);
	if (keysym == 65453)
		less_key(fdf);
	if (keysym == 65435)
		plus_pitch(fdf);
	if (keysym == 65433)
		less_pitch(fdf);
	if (keysym == 65429)
		plus_yaw(fdf);
	if (keysym == 65430)
		less_yaw(fdf);
	if (keysym == 65431)
		plus_roll(fdf);
	if (keysym == 65432)
		less_roll(fdf);
	return (0);
}

int	key_press(int keysym, t_fdf *fdf)
{
	if (keysym >= 65361 && keysym <= 65364)
		return (arrows(keysym, fdf));
	if (keysym == 65438 || keysym == 65436
		|| keysym == 65434 || keysym == 65437)
		return (views(keysym, fdf));
	if ((keysym >= 65429 && keysym <= 65433)
		|| keysym == 65451
		|| keysym == 65453
		|| keysym == 65435)
		return (rotations(keysym, fdf));
	if (keysym == 65307)
		ctrl_cancel(fdf);
	return (0);
}
