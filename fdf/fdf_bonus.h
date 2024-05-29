/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:56:53 by mastie            #+#    #+#             */
/*   Updated: 2022/12/06 22:38:23 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "mlx/mlx.h"
# include <math.h>

# ifndef HEIGHT
#  define HEIGHT 1300
# endif
# ifndef WIDTH
#  define WIDTH 1900
# endif	

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	float	dx;
	float	dy;
	float	dz;
	int		color;

}				t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}				t_img;

typedef struct s_fdf
{
	t_point	**pmap;

	int		img_width;
	int		img_height;

	int		x_limit;
	int		y_limit;
	int		z_limit;

	int		x_shift;
	int		y_shift;

	int		x_draw;
	int		y_draw;
	int		z_draw;

	int		redraw;
	int		repos;
	int		view;
	int		rotate;
	int		colored;

	float	x_angle;
	float	y_angle;
	float	z_angle;

	int		zoom;
	int		color;
	void	*mlx;
	void	*win;
	t_img	img;

}			t_fdf;

	/*PARSER PARTS*/

int		color_input_is_valid(char *color);
int		int_input_is_valid(char *nbr);
int		get_ints_and_colors_point(t_fdf *fdf, char *content, int y_c);
int		parser(t_fdf *fdf, char *map_name);

	/*DRAW PARTS*/

void	conique(float *x, float *y, int z);
void	parallele(float *x, float *y, int z);
void	isometric(float *x, float *y, int z);
void	set_for_rotate(t_fdf *fdf);
void	position_to_draw(t_fdf *fdf);
void	draw(t_fdf *fdf);

	/*FREE PARTS*/

void	free_map(t_fdf *fdf);
void	free_char_tab(char **tab);

	/*HOOK PART*/

int		key_press(int keysym, t_fdf *fdf);
int		exposure(t_fdf *fdf);

	/*KEY PRESS PART*/

void	plus_key(t_fdf *fdf);
void	less_key(t_fdf *fdf);
void	ctrl_cancel(t_fdf *fdf);
void	down_arrow(t_fdf *fdf);
void	right_arrow(t_fdf *fdf);
void	up_arrow(t_fdf *fdf);
void	left_arrow(t_fdf *fdf);
void	less_pitch(t_fdf *fdf);
void	less_yaw(t_fdf *fdf);
void	less_roll(t_fdf *fdf);
void	plus_pitch(t_fdf *fdf);
void	plus_yaw(t_fdf *fdf);
void	plus_roll(t_fdf *fdf);
void	isometric_view(t_fdf *fdf);
void	parallele_view(t_fdf *fdf);
void	conique_view(t_fdf *fdf);
void	reset_flat(t_fdf *fdf);

	/*AXE ROTATION*/

void	rotate(t_point *from, t_point *to, t_fdf *fdf);

	/* UTILS*/

void	zoom(t_point *point, int zoom);
void	zoomed(t_point *a, t_point *b, t_fdf *fdf);
void	colored(t_point a, t_point b, t_fdf *fdf);
int		is_charset(char c, char *charset);

	/* ABSOLU */

int		max_absolu(float a, float b);
float	absolu(float a);

#endif
