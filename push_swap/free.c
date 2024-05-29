/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:18:22 by mastie            #+#    #+#             */
/*   Updated: 2022/12/12 22:18:24 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_piles(t_operator *operator)
{
	t_pile	*tmp;

	while ((*operator).a)
	{
		tmp = (*operator).a->next;
		free((*operator).a);
		(*operator).a = tmp;
	}
}
