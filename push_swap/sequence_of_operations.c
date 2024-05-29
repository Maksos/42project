/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_of_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:12:39 by mastie            #+#    #+#             */
/*   Updated: 2023/01/09 18:12:40 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Prend le premier élément au sommet de a et le met sur b.
// Ne fait rien si a est vide.
void	pb(t_operator *operator)
{
	t_pile	*tmp;
	t_pile	*new;

	new = lst_new((*operator).a->value);
	tmp = (*operator).a;
	(*operator).a = (*operator).a->next;
	free(tmp);
	new->next = (*operator).b;
	(*operator).b = new;
	write(1, "pb\n", 3);
}

// Intervertit les 2 premiers éléments au sommet de la pile a.
// Ne fait rien s’il n’y en a qu’un ou aucun
void	sa(t_operator *operator)
{
	int	tmp;

	tmp = (*operator).a->value;
	(*operator).a->value = (*operator).a->next->value;
	(*operator).a->next->value = tmp;
	write(1, "sa\n", 3);
}

// Intervertit les 2 premiers éléments au sommet de la pile b.
// Ne fait rien s’il n’y en a qu’un ou aucun
void	sb(t_operator *operator)
{
	int	tmp;

	tmp = (*operator).b->value;
	(*operator).b->value = (*operator).b->next->value;
	(*operator).b->next->value = tmp;
	write(1, "sb\n", 3);
}
