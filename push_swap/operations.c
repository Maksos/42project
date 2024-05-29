/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:28:19 by mastie            #+#    #+#             */
/*   Updated: 2022/12/28 13:28:21 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Décale d’une position vers le bas tous les élements de
// la pile a. Le dernier élément devient le premier.
void	rra(t_operator *operator, int print)
{
	t_pile	*tmp;
	t_pile	*new;
	t_pile	*last;

	tmp = (*operator).a;
	while (tmp && tmp->next)
	{
		last = tmp;
		tmp = tmp->next;
	}
	new = lst_new(tmp->value);
	free(tmp);
	last->next = NULL;
	new->next = (*operator).a;
	(*operator).a = new;
	if (print == 1)
		write(1, "rra\n", 4);
}

// Décale d’une position vers le bas tous les élements de
// la pile b. Le dernier élément devient le premier.
void	rrb(t_operator *operator, int print)
{
	t_pile	*tmp;
	t_pile	*new;
	t_pile	*last;

	tmp = (*operator).b;
	while (tmp && tmp->next)
	{
		last = tmp;
		tmp = tmp->next;
	}
	new = lst_new(tmp->value);
	free(tmp);
	last->next = NULL;
	new->next = (*operator).b;
	(*operator).b = new;
	if (print == 1)
		write(1, "rrb\n", 4);
}

// Décale d’une position vers le haut tous les élements de la pile a.
// Le premier élément devient le dernier.
void	ra(t_operator *operator, int print)
{
	t_pile	*tmp;
	t_pile	*new;

	tmp = (*operator).a;
	new = lst_new((*operator).a->value);
	(*operator).a = (*operator).a->next;
	free(tmp);
	tmp = (*operator).a;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	if (print == 1)
		write(1, "ra\n", 3);
}

// Décale d’une position vers le haut tous les élements de la pile b.
// Le premier élément devient le dernier.
void	rb(t_operator *operator, int print)
{
	t_pile	*tmp;
	t_pile	*new;

	tmp = (*operator).b;
	new = lst_new((*operator).b->value);
	(*operator).b = (*operator).b->next;
	free(tmp);
	tmp = (*operator).b;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	if (print == 1)
		write(1, "rb\n", 3);
}

// Prend le premier élément au sommet de b et le met sur a.
// Ne fait rien si b est vide.
void	pa(t_operator *operator)
{
	t_pile	*tmp;
	t_pile	*new;

	new = lst_new((*operator).b->value);
	tmp = (*operator).b;
	(*operator).b = (*operator).b->next;
	free(tmp);
	new->next = (*operator).a;
	(*operator).a = new;
	write(1, "pa\n", 3);
}
