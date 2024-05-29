/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:38:30 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 20:38:32 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insert_this_one(t_operator *operator, int this_one)
{
	t_pile	*tmp;
	int		i;

	i = 0;
	tmp = (*operator).a;
	while (tmp)
	{
		if (i == this_one)
			return (act_for_this_one(operator, tmp));
		tmp = tmp->next;
		i++;
	}
}

void	insert_lower_hit(t_operator *operator)
{
	t_pile	*tmp;
	int		lower[4];

	lower[1] = lst_count((*operator).a) + lst_count((*operator).b);
	lower[2] = 0;
	tmp = (*operator).a;
	while (tmp)
	{
		lower[0] = tmp->rra;
		lower[0] += (tmp->rrb + tmp->ra + tmp->rb);
		if (lower[0] < lower[1])
		{
			lower[1] = lower[0];
			lower[3] = lower[2];
		}
		tmp = tmp->next;
		lower[2]++;
	}
	return (insert_this_one(operator, lower[3]));
}

void	b_insert_counter(t_operator *operator, t_pile *current)
{
	if (current_is_new_max(operator, current) == 1)
		return (rotate_old_max_to_head(operator, current));
	else if (current_is_new_min(operator, current) == 1)
		return (rotate_old_max_to_head(operator, current));
	else
		return (rotate_superior_current_to_head(operator, current));
}

void	extract_insert(t_operator *operator)
{
	pb(operator);
	pb(operator);
	while ((*operator).a != NULL)
	{
		hit_counter(operator);
		insert_lower_hit(operator);
	}
}

void	hit_counter(t_operator *operator)
{
	t_pile	*tmp;
	int		i;

	tmp = (*operator).a;
	i = 0;
	while (tmp)
	{
		reset_counter(tmp);
		a_extract_counter(operator, tmp, i);
		b_insert_counter(operator, tmp);
		tmp = tmp->next;
		i++;
	}
}
