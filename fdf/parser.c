/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:56:59 by mastie            #+#    #+#             */
/*   Updated: 2022/11/24 21:43:18 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fill_map_rows(t_fdf *fdf, t_list *mapper)
{
	int	y;

	y = 0;
	while (y < (*fdf).y_limit)
	{
		if (get_ints_and_colors_point(fdf, (char *)mapper->content, y) == -1)
			return (-1);
		y++;
		mapper = mapper->next;
	}
	return (0);
}

int	init_map_cols(t_fdf *fdf)
{
	int	i;

	i = 0;
	(*fdf).pmap = malloc(sizeof(t_point *) * (*fdf).y_limit);
	if ((*fdf).pmap == NULL)
		return (-1);
	while (i < (*fdf).y_limit)
	{
		(*fdf).pmap[i] = NULL;
		i++;
	}
	return (0);
}

int	fill_map_point(t_fdf *fdf, t_list *mapper)
{
	int	ret;

	ret = init_map_cols(fdf);
	if (ret == -1)
	{
		ft_lstclear(&mapper, &free);
		return (-1);
	}
	ret = fill_map_rows(fdf, mapper);
	if (ret == -1)
	{
		free_map(fdf);
		ft_lstclear(&mapper, &free);
		return (-1);
	}
	ft_lstclear(&mapper, &free);
	return (0);
}

int	parser(t_fdf *fdf, char *map_name)
{
	t_list	*mapper;
	int		map_fd;
	char	*line;

	mapper = NULL;
	map_fd = open(map_name, O_RDONLY, S_IWUSR);
	if (map_fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(map_fd);
		if (line == NULL)
			break ;
		ft_lstadd_back(&mapper, ft_lstnew(ft_strtrim(line, "\n")));
		free(line);
		line = NULL;
		(*fdf).y_limit++;
	}
	if (close(map_fd) == -1)
		return (-1);
	return (fill_map_point(fdf, mapper));
}
