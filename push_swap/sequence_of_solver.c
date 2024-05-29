/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_of_solver.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:18 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 20:33:20 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	current_max_is_head(t_operator *operator)
{
	t_pile	*tmp;

	tmp = (*operator).b->next;
	while (tmp)
	{
		if (tmp->value > (*operator).b->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	current_is_new_max(t_operator *operator, t_pile *current)
{
	t_pile	*tmp;

	tmp = (*operator).b;
	while (tmp)
	{
		if (tmp->value > current->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	current_is_new_min(t_operator *operator, t_pile *current)
{
	t_pile	*tmp;

	tmp = (*operator).b;
	while (tmp)
	{
		if (tmp->value < current->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	nothing_supp(t_pile *to_test, t_pile *current)
{
	t_pile	*tmp;

	tmp = to_test->next;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->value < to_test->value || current->value > tmp->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	reset_counter(t_pile *current)
{
	current->rra = 0;
	current->rrb = 0;
	current->ra = 0;
	current->rb = 0;
}
