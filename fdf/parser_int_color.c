/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:32:28 by mastie            #+#    #+#             */
/*   Updated: 2022/11/30 22:32:38 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fill_int_color_point(t_fdf *fdf, char **dot_color, int y_c, int x_c)
{
	char	*hex_to_dec;
	char	*tmp;

	if (int_input_is_valid(dot_color[0]) == -1)
		return (-1);
	if (color_input_is_valid(dot_color[1]) == -1)
		return (-1);
	tmp = ft_substr(dot_color[1], 2, ft_strlen(dot_color[1]));
	hex_to_dec = ft_convert_base(tmp, "0123456789abcdef", "0123456789");
	free(tmp);
	(*fdf).pmap[y_c][x_c].x = x_c;
	(*fdf).pmap[y_c][x_c].y = y_c;
	(*fdf).pmap[y_c][x_c].z = ft_atoi(dot_color[0]);
	(*fdf).pmap[y_c][x_c].color = ft_atoi(hex_to_dec);
	free(hex_to_dec);
	return (0);
}

int	color_flag_on_point(t_fdf *fdf, char *dot_color, int y_c, int x_c)
{
	char	**dot_and_color;

	(*fdf).colored = 1;
	dot_and_color = ft_split(dot_color, ',');
	if (dot_and_color == NULL)
		return (-1);
	if (fill_int_color_point(fdf, dot_and_color, y_c, x_c) == -1)
	{
		free_char_tab(dot_and_color);
		return (-1);
	}
	free_char_tab(dot_and_color);
	return (0);
}

int	fill_by_flag_point(t_fdf *fdf, char **dots, int y_c)
{
	int		x;

	x = 0;
	while (dots && dots[x])
	{
		if (ft_strchr(dots[x], ',') != NULL)
		{
			if (color_flag_on_point(fdf, dots[x], y_c, x) == -1)
				return (-1);
		}
		else
		{
			if (int_input_is_valid(dots[x]) == -1)
				return (-1);
			(*fdf).pmap[y_c][x].x = x;
			(*fdf).pmap[y_c][x].y = y_c;
			(*fdf).pmap[y_c][x].z = ft_atoi(dots[x]);
			(*fdf).pmap[y_c][x].color = 16777215;
		}
		if (absolu((*fdf).pmap[y_c][x].z) > (*fdf).z_limit)
			(*fdf).z_limit = absolu((*fdf).pmap[y_c][x].z) + 1;
		x++;
	}
	return (0);
}

int	get_ints_colors_point(t_fdf *fdf, char **dots, int y_c)
{
	int		x;

	x = 0;
	while (dots && dots[x])
		x++;
	if ((*fdf).x_limit == 0)
		(*fdf).x_limit = x;
	else if ((*fdf).x_limit != x)
		return (-1);
	(*fdf).pmap[y_c] = malloc(sizeof(t_point) * (*fdf).x_limit);
	if ((*fdf).pmap[y_c] == NULL)
		return (-1);
	return (fill_by_flag_point(fdf, dots, y_c));
}

int	get_ints_and_colors_point(t_fdf *fdf, char *content, int y_c)
{
	char	**dots;

	dots = ft_split(content, ' ');
	if (dots == NULL)
		return (-1);
	if (get_ints_colors_point(fdf, dots, y_c) == -1)
	{
		free_char_tab(dots);
		(*fdf).y_limit = y_c + 1;
		return (-1);
	}
	free_char_tab(dots);
	return (0);
}
