/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:57:15 by mastie            #+#    #+#             */
/*   Updated: 2022/11/02 16:05:33 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_cols_map(t_fdf *fdf)
{
	int	y;

	y = 0;
	while (y < (*fdf).y_limit)
	{
		free((*fdf).pmap[y]);
		y++;
	}
}

void	free_map(t_fdf *fdf)
{
	if ((*fdf).pmap && (*fdf).pmap != NULL)
		free_cols_map(fdf);
	if ((*fdf).pmap)
		free((*fdf).pmap);
}

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}
