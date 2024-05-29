/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:13:17 by mastie            #+#    #+#             */
/*   Updated: 2022/12/05 13:13:18 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	add_new_to_a(t_pile **a, t_pile *new)
{
	t_pile	*tmp;

	if (a && *a)
	{
		tmp = *a;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*a = new;
}

t_pile	*lst_new(int value)
{
	t_pile	*new;

	new = malloc(sizeof(t_pile));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->rra = 0;
	new->ra = 0;
	new->rrb = 0;
	new->rb = 0;
	new->next = NULL;
	return (new);
}

int	sorted(t_operator *operator)
{
	t_pile	*tmp;

	tmp = (*operator).a;
	while (tmp)
	{
		if (tmp->next && tmp->value > tmp->next->value)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_piles(t_operator *operator)
{
	t_pile	*atmp;
	t_pile	*btmp;
	int		i;

	i = 0;
	atmp = (*operator).a;
	btmp = (*operator).b;
	ft_printf("\n");
	while (atmp)
	{
		ft_printf("[%d]operator.A[%d]\n", i, atmp->value);
		atmp = atmp->next;
		i++;
	}
	i = 0;
	ft_printf("\n");
	while (btmp)
	{
		ft_printf("[%d]operator.B[%d]\n", i, btmp->value);
		btmp = btmp->next;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_operator	operator;

	if (ac > 1)
	{
		operator.args = NULL;
		operator.a = NULL;
		operator.b = NULL;
		if (parser(&operator, av, ac) == -1)
		{
			ft_printf("Error in parse\n");
			return (-1);
		}
		ft_lstclear(&(operator).args, free);
		solver(&operator);
		free_piles(&operator);
	}
	else
	{
		ft_printf("Error\nUsage ./pushswap 5 4 \"3 5\" 2 1\n");
		return (-1);
	}
	return (0);
}
