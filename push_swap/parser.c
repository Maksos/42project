/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:05:14 by mastie            #+#    #+#             */
/*   Updated: 2022/12/12 22:05:16 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_digit(char *args)
{
	int	i;

	i = 0;
	if (args && args[i] == '-')
		i++;
	while (args && args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	get_args(t_operator *operator, char *input)
{
	char	**input_args;
	int		i;

	i = 0;
	input_args = ft_split(input, ' ');
	if (input_args == NULL)
		return (0);
	while (input_args && input_args[i])
	{
		if (check_digit(input_args[i]) == -1)
		{
			free_char_tab(input_args);
			return (-1);
		}
		ft_lstadd_back(&(*operator).args, ft_lstnew(ft_strdup(input_args[i])));
		i++;
	}
	free_char_tab(input_args);
	return (0);
}

int	check_singleton(t_operator *operator)
{
	t_pile	*tmp;
	t_pile	*ttmp;

	tmp = (*operator).a;
	while (tmp)
	{
		if (tmp->next)
		{
			ttmp = tmp->next;
			while (ttmp)
			{
				if (tmp->value == ttmp->value)
					return (-1);
				ttmp = ttmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	list_to_pile(t_operator *operator)
{
	t_list	*tmp;
	t_pile	*new;
	int		value;

	tmp = (*operator).args;
	while (tmp)
	{
		value = ft_atoi((char *)tmp->content);
		if ((value == 0 && ft_strlen((char *)tmp->content) > 2))
		{
			ft_printf("[%s][%d]\n", (char *)tmp->content, value);
			free_piles(operator);
			return (-1);
		}
		new = lst_new(value);
		if (new == NULL)
		{
			free_piles(operator);
			return (-1);
		}
		add_new_to_a(&(*operator).a, new);
		tmp = tmp->next;
	}
	return (0);
}

int	parser(t_operator *operator, char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (get_args(operator, av[i]) == -1)
		{
			ft_lstclear(&(*operator).args, free);
			return (-1);
		}
		i++;
	}
	if (list_to_pile(operator) == -1)
	{
		free_piles(operator);
		ft_lstclear(&(*operator).args, free);
		return (-1);
	}
	ft_lstclear(&(*operator).args, free);
	if (check_singleton(operator) == -1)
	{
		free_piles(operator);
		return (-1);
	}
	return (0);
}
