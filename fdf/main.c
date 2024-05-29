/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:56:47 by mastie            #+#    #+#             */
/*   Updated: 2022/11/25 03:19:50 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	imaging(t_fdf *fdf)
{
	(*fdf).img.img = mlx_new_image((*fdf).mlx,
			(*fdf).img_width, (*fdf).img_height);
	if ((*fdf).img.img == NULL)
	{
		mlx_destroy_display((*fdf).mlx);
		free((*fdf).mlx);
		free_map(fdf);
		exit(EXIT_FAILURE);
	}
	(*fdf).img.addr = mlx_get_data_addr((*fdf).img.img,
			&(*fdf).img.bits_per_pixel,
			&(*fdf).img.line_length, &(*fdf).img.endian);
	draw(fdf);
}

int	loop_check(t_fdf *fdf)
{
	if ((*fdf).redraw == 1)
	{
		mlx_destroy_image((*fdf).mlx, (*fdf).img.img);
		mlx_clear_window((*fdf).mlx, (*fdf).win);
		imaging(fdf);
		(*fdf).repos = 1;
		(*fdf).redraw = 0;
	}
	if ((*fdf).repos == 1)
	{
		(*fdf).repos = 0;
		mlx_clear_window((*fdf).mlx, (*fdf).win);
		mlx_put_image_to_window((*fdf).mlx, (*fdf).win,
			(*fdf).img.img, (*fdf).x_shift, (*fdf).y_shift);
	}
	return (0);
}

int	init_mlx(t_fdf *fdf)
{
	(*fdf).mlx = mlx_init();
	if ((*fdf).mlx == NULL)
		return (-1);
	(*fdf).win = mlx_new_window((*fdf).mlx, WIDTH, HEIGHT, "FDF");
	if ((*fdf).win == NULL)
	{
		mlx_destroy_display((*fdf).mlx);
		free((*fdf).mlx);
		return (-1);
	}
	position_to_draw(fdf);
	imaging(fdf);
	mlx_put_image_to_window((*fdf).mlx, (*fdf).win, (*fdf).img.img,
		(*fdf).x_shift, (*fdf).y_shift);
	mlx_hook((*fdf).win, 2, 1L << 0, key_press, fdf);
	mlx_hook((*fdf).win, 17, 1L << 15, exposure, fdf);
	mlx_loop_hook((*fdf).mlx, loop_check, fdf);
	mlx_loop((*fdf).mlx);
	return (0);
}

void	set_fdf(t_fdf *fdf)
{
	(*fdf).x_shift = 0;
	(*fdf).y_shift = 0;
	(*fdf).y_limit = 0;
	(*fdf).x_limit = 0;
	(*fdf).z_limit = 0;
	(*fdf).x_angle = 0.0;
	(*fdf).y_angle = 0.0;
	(*fdf).z_angle = 0.0;
	(*fdf).redraw = 0;
	(*fdf).repos = 0;
	(*fdf).rotate = 0;
	(*fdf).colored = 0;
	(*fdf).view = 4;
	(*fdf).x_draw = 0;
	(*fdf).y_draw = 0;
	(*fdf).z_draw = 0;
	(*fdf).zoom = 5;
	(*fdf).mlx = NULL;
	(*fdf).win = NULL;
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	set_fdf(&fdf);
	if (ac != 2)
	{
		ft_printf("Error usage\n\"./fdf map_path_name\"\n");
		return (-1);
	}
	if (parser(&fdf, av[1]) == -1)
	{
		ft_printf("Error in parser\n");
		return (-1);
	}
	if (init_mlx(&fdf) == -1)
	{
		free_map(&fdf);
		return (-1);
	}
	return (0);
}
