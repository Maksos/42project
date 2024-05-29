/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:15:43 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/18 19:51:40 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_next_node_and(t_cmd *current, t_core *core)
{
	if (current->pipes)
		skip_next_node_and(current->pipes, core);
	else if (current->and)
		skip_next_node_and(current->and, core);
	else if (current->or)
		recursive_exec(current->or, core);
}

void	skip_next_node_or(t_cmd *current, t_core *core)
{
	if (current->pipes)
		skip_next_node_or(current->pipes, core);
	else if (current->and)
		recursive_exec(current->and, core);
	else if (current->or)
		skip_next_node_or(current->or, core);
}

void	exec_node_and(t_cmd *current, t_core *core)
{
	if (current->parenthesis)
		recursive_exec(current->parenthesis, core);
	else
		exec_ast_node(current->data, core);
	if (g_exit_status == 0)
		recursive_exec(current->and, core);
	else
		skip_next_node_and(current->and, core);
}

void	exec_node_or(t_cmd *current, t_core *core)
{
	if (current->parenthesis)
		recursive_exec(current->parenthesis, core);
	else
		exec_ast_node(current->data, core);
	if (g_exit_status != 0)
		recursive_exec(current->or, core);
	else
		skip_next_node_or(current->or, core);
}
