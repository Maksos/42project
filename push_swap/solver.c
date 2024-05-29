/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 01:39:23 by mastie            #+#    #+#             */
/*   Updated: 2022/12/13 01:39:25 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	lst_count(t_pile *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	a_extract_counter(t_operator *operator, t_pile *current, int i)
{
	int		median;
	int		lst_c;

	if (i == 0)
		return ;
	lst_c = lst_count((*operator).a);
	median = lst_c / 2;
	if (i > median)
		current->rra = lst_c - i;
	else
		current->ra = i;
}

void	act_for_this_one(t_operator *operator, t_pile *this_one)
{
	int	i[5];

	i[0] = this_one->rra;
	i[1] = this_one->rrb;
	i[2] = this_one->ra;
	i[3] = this_one->rb;
	rrr(operator, i[0], i[1]);
	rr(operator, i[2], i[3]);
	pb(operator);
}

void	solver(t_operator *operator)
{
	int	lst_c;

	lst_c = lst_count((*operator).a);
	if (sorted(operator) == 0)
		return ;
	else if (lst_c == 3)
		return (solver_3(operator));
	else if (lst_c == 5)
		return (solver_5(operator));
	extract_insert(operator);
	rotate_max_head(operator);
	while ((*operator).b != NULL)
		pa(operator);
}
