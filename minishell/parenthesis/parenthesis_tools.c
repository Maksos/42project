/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:35:01 by mastie            #+#    #+#             */
/*   Updated: 2023/10/17 04:25:44 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_in_t_list_follow(t_list *to_free, t_list **current_to_free)
{
	t_list	*tmp;
	t_list	*tmp_to_free;

	tmp = *current_to_free;
	while (tmp && tmp->next)
	{
		if (to_free && tmp->next == to_free)
		{
			tmp_to_free = to_free->next;
			tmp->next = tmp_to_free;
			free(to_free->content);
			free(to_free);
			to_free = NULL;
		}
		else
			tmp = tmp->next;
	}
}

void	free_in_t_list(t_list *to_free, t_list **current_to_free)
{
	t_list	*tmp;
	t_list	*tmp_to_free;

	tmp = *current_to_free;
	if (tmp == to_free && !tmp->next)
	{
		free(tmp->content);
		free(tmp);
		*current_to_free = NULL;
	}
	else if (tmp == to_free)
	{
		tmp_to_free = tmp;
		tmp = tmp->next;
		free(tmp_to_free->content);
		free(tmp_to_free);
		tmp_to_free = NULL;
		*current_to_free = tmp;
	}
	else
		free_in_t_list_follow(to_free, current_to_free);
}

void	fill_and_free_parenthesis(t_list *tmp_l, t_list *tmp_r, t_core *core)
{
	int		lparen_int;
	int		rparen_int;

	lparen_int = ((t_parenthes *)tmp_l->content)->position;
	rparen_int = ((t_parenthes *)tmp_r->content)->position;
	ft_lstadd_back(&core->current_parenthesis,
		ft_lstnew(new_t_parenthesis(lparen_int, rparen_int)));
	free_in_t_list(tmp_l, &core->lparenthesis);
	free_in_t_list(tmp_r, &core->rparenthesis);
	return (checking_parenthesis(core));
}

void	checking_parenthesis(t_core *core)
{
	t_list	*tmp_l;
	t_list	*tmp_r;

	tmp_l = core->lparenthesis;
	tmp_r = core->rparenthesis;
	if (!core->lparenthesis && !core->rparenthesis)
		return ;
	while (tmp_l)
	{
		if (tmp_l->next && ((t_parenthes *)tmp_r->content)->position
			> ((t_parenthes *)tmp_l->content)->position)
		{
			if (((t_parenthes *)tmp_r->content)->position
				< ((t_parenthes *)tmp_l->next->content)->position)
				return (fill_and_free_parenthesis(tmp_l, tmp_r, core));
		}
		else if (!tmp_l->next && ((t_parenthes *)tmp_r->content)->position
			> ((t_parenthes *)tmp_l->content)->position)
			return (fill_and_free_parenthesis(tmp_l, tmp_r, core));
		tmp_l = tmp_l->next;
	}
}
