/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrr_rr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:42:13 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 21:42:14 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_operator *operator, int r_a, int r_b)
{
	while (r_a > 0 && r_b > 0)
	{
		ra(operator, 0);
		rb(operator, 0);
		write(1, "rr\n", 3);
		r_a--;
		r_b--;
	}
	while (r_a > 0)
	{
		ra(operator, 1);
		r_a--;
	}
	while (r_b > 0)
	{
		rb(operator, 1);
		r_b--;
	}
}

void	rrr(t_operator *operator, int r_ra, int r_rb)
{
	while (r_ra > 0 && r_rb > 0)
	{
		rra(operator, 0);
		rrb(operator, 0);
		write(1, "rrr\n", 4);
		r_ra--;
		r_rb--;
	}
	while (r_ra > 0)
	{
		rra(operator, 1);
		r_ra--;
	}
	while (r_rb > 0)
	{
		rrb(operator, 1);
		r_rb--;
	}
}
