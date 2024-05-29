/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_ast_by_operators.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:48:24 by mastie            #+#    #+#             */
/*   Updated: 2023/09/07 16:53:11 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipes	*new_t_pipes(t_content *data)
{
	t_pipes	*new;

	new = malloc(sizeof(t_pipes));
	if (new == NULL)
		return (NULL);
	new->data = data;
	new->fork_id = -1;
	return (new);
}

int	struct_to_ast_by_and_or(t_token *current, t_core *core)
{
	if (current->id == 3)
	{
		core->current->and = new_t_cmd();
		if (core->current->and == NULL)
			return (-1);
		core->current = core->current->and;
	}
	else
	{
		core->current->or = new_t_cmd();
		if (core->current->or == NULL)
			return (-1);
		core->current = core->current->or;
	}
	core->current_data = NULL;
	return (0);
}

int	struct_to_ast_by_pipe(t_core *core)
{
	core->current->pipes = new_t_cmd();
	if (core->current->pipes == NULL)
		return (-1);
	core->current = core->current->pipes;
	core->current_data = core->current->data;
	return (0);
}
