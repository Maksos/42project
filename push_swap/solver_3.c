/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 23:11:08 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 23:11:09 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sequence_of_solver_3(t_operator *operator)
{
	sa(operator);
	ra(operator, 1);
}

void	sequence_2_of_solver_3(t_operator *operator)
{
	rra(operator, 1);
	rra(operator, 1);
}

void	sequence_3_of_solver_3(t_operator *operator)
{
	sa(operator);
	rra(operator, 1);
}

void	solver_3(t_operator *operator)
{
	t_pile	*a;
	t_pile	*b;
	t_pile	*c;

	a = (*operator).a;
	b = a->next;
	c = b->next;
	if (a->value > b->value && b->value < c->value && a->value < c->value)
		sa(operator);
	else if (a->value < b->value && b->value > c->value && a->value < c->value)
		sequence_of_solver_3(operator);
	else if (a->value > b->value && b->value < c->value && a->value > c->value)
		sequence_2_of_solver_3(operator);
	else if (a->value > b->value && b->value > c->value && c->value < a->value)
		sequence_3_of_solver_3(operator);
	else if (a->value < b->value && b->value > c->value && c->value < a->value)
		rra(operator, 1);
}
