/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_ast_by_parenthesis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:46:32 by mastie            #+#    #+#             */
/*   Updated: 2023/09/07 16:54:04 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	struct_to_ast_by_lparen(t_core *core)
{
	core->current->parenthesis = new_t_cmd();
	if (core->current->parenthesis == NULL)
		return (-1);
	ft_lstadd_front(&core->current_parenthesis, ft_lstnew(core->current));
	core->current = core->current->parenthesis;
	core->current_data = core->current->data;
	return (0);
}

int	struct_to_ast_by_rparen(t_core *core)
{
	t_list	*tmp;

	tmp = core->current_parenthesis;
	if (tmp)
	{
		core->parenthesis_parent = (t_cmd *)tmp->content;
		core->current_parenthesis = core->current_parenthesis->next;
		free(tmp);
		tmp = NULL;
		core->current = core->parenthesis_parent;
		if (!core->current_parenthesis)
			core->parenthesis_parent = NULL;
		return (0);
	}
	return (-1);
}
