/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 23:11:13 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 23:11:14 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	extract_this_one(t_operator *operator, int this)
{
	int	lst_c;

	lst_c = lst_count((*operator).a);
	if (this <= 2)
	{
		while (this > 0)
		{
			ra(operator, 1);
			this--;
		}
	}
	else if (this > 2)
	{
		while (this < lst_c)
		{
			rra(operator, 1);
			this++;
		}
	}
	pb(operator);
}

void	extract_lowest(t_operator *operator)
{
	t_pile	*tmp;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	tmp = (*operator).a;
	i[2] = tmp->value;
	while (tmp)
	{
		if (tmp->value < i[2])
		{
			i[1] = i[0];
			i[2] = tmp->value;
		}
		tmp = tmp->next;
		i[0]++;
	}
	extract_this_one(operator, i[1]);
}

void	solver_5(t_operator *operator)
{
	extract_lowest(operator);
	extract_lowest(operator);
	solver_3(operator);
	pa(operator);
	pa(operator);
}
