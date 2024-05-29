/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_in_expanded_dollar.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:15:19 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/04 19:33:00 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space_sep(char *c)
{
	if (*c == '\t' || *c == '\n' || *c == '\v'
		|| *c == '\f' || *c == '\r' || *c == ' ')
		return (0);
	return (1);
}

int	check_replace_dollar_space(t_list *current, t_list *expand)
{
	char	*str;
	t_list	*tmp;

	str = (char *)current->content;
	if (ft_memchr(str, '$', ft_strlen(str)) != NULL)
	{
		tmp = expand;
		while (tmp)
		{
			if (is_space_sep((char *)tmp->content) == 0)
				return (0);
			tmp = tmp->next;
		}
		return (1);
	}
	return (1);
}

char	*combine_char_to_arg(t_list *expand, t_core *core)
{
	t_list	*tmp;
	char	*ret;
	int		size;

	tmp = expand;
	size = 0;
	while (tmp && is_space_sep((char *)tmp->content) != 0)
	{
		size++;
		tmp = tmp->next;
	}
	ret = malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		ft_perror_exit("Minishell ", errno, core);
	tmp = expand;
	size = 0;
	while (tmp && is_space_sep((char *)tmp->content) != 0)
	{
		ret[size] = *(char *)tmp->content;
		size++;
		tmp = tmp->next;
	}
	ret[size] = '\0';
	return (ret);
}

void	join_new_args_from_t_list(t_list *current, t_list *to_add)
{
	t_list	*to_free;

	to_free = to_add;
	free(current->content);
	current->content = to_add->content;
	ft_lstadd_back(&to_add, current->next);
	to_add = to_add->next;
	free(to_free);
	current->next = to_add;
}

void	replace_space_by_args(t_list *current, t_list *expand, t_core *core)
{
	t_list	*insert_args;
	t_list	*save_expand;

	save_expand = expand;
	insert_args = NULL;
	while (expand)
	{
		if (is_space_sep((char *)expand->content) == 0)
		{
			while (expand && is_space_sep((char *)expand->content) == 0)
				expand = expand->next;
		}
		else
		{
			ft_lstadd_back(&insert_args,
				ft_lstnew(combine_char_to_arg(expand, core)));
			while (expand && is_space_sep((char *)expand->content) != 0)
				expand = expand->next;
		}
	}
	join_new_args_from_t_list(current, insert_args);
	free_t_list(save_expand, 1);
}
