/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:42:24 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 20:42:25 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rrb_or_rb(t_pile *current, int i_old_max, int b_lst_c)
{
	int	median;

	if (i_old_max == 0)
		return ;
	median = b_lst_c / 2;
	if (i_old_max > median)
		current->rrb = b_lst_c - i_old_max;
	else
		current->rb = i_old_max;
}

void	rotate_old_max_to_head(t_operator *operator, t_pile *current)
{
	int		i[3];
	t_pile	*tmp;

	tmp = (*operator).b;
	i[0] = 0;
	i[1] = 0;
	i[2] = tmp->value;
	while (tmp)
	{
		if (tmp->value > i[2])
		{
			i[1] = i[0];
			i[2] = tmp->value;
		}
		tmp = tmp->next;
		i[0]++;
	}
	return (rrb_or_rb(current, i[1], lst_count((*operator).b)));
}

void	rotate_the_max_to_head(t_operator *operator, int is_at)
{
	int	median;
	int	lst_c;

	lst_c = lst_count((*operator).b);
	median = lst_c / 2;
	if (is_at > median)
	{
		while (is_at < lst_c)
		{
			rrb(operator, 1);
			is_at++;
		}
	}
	else
	{
		while (is_at > 0)
		{
			rb(operator, 1);
			is_at--;
		}
	}	
}

void	rotate_max_head(t_operator *operator)
{
	int		i[3];
	t_pile	*tmp;

	tmp = (*operator).b;
	i[0] = 0;
	i[1] = 0;
	i[2] = tmp->value;
	while (tmp)
	{
		if (tmp->value > i[2])
		{
			i[1] = i[0];
			i[2] = tmp->value;
		}
		tmp = tmp->next;
		i[0]++;
	}
	return (rotate_the_max_to_head(operator, i[1]));
}

void	rotate_superior_current_to_head(t_operator *operator, t_pile *current)
{
	t_pile	*tmp;
	int		i[2];

	i[0] = 0;
	tmp = (*operator).b;
	while (tmp && tmp->next)
	{
		if (tmp->value < current->value && current->value < tmp->next->value
			&& nothing_supp(tmp->next, current) == 1)
			return (rrb_or_rb(current, i[0] + 1, lst_count((*operator).b)));
		else if (tmp->value > current->value
			&& current->value > tmp->next->value)
			return (rrb_or_rb(current, i[0] + 1, lst_count((*operator).b)));
		tmp = tmp->next;
		i[0]++;
	}
	if (!tmp->next)
	{
		if (tmp->value < current->value
			&& current->value < (*operator).b->value)
			return (rrb_or_rb(current, i[0], lst_count((*operator).b)));
		else if (tmp->value > current->value
			&& current->value > (*operator).b->value)
			return (rrb_or_rb(current, 0, lst_count((*operator).b)));
	}
}
