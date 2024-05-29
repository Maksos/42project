/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:11:42 by mastie            #+#    #+#             */
/*   Updated: 2023/11/06 18:23:13 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_fds(int fd_pipe[2])
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
}

int	recursive_exec(t_cmd *current, t_core *core)
{
	int	ret_status;

	ret_status = 0;
	if (current->pipes)
		ret_status = exec_node_pipe(current, core);
	else if (current->and)
		exec_node_and(current, core);
	else if (current->or)
		exec_node_or(current, core);
	else if (current->parenthesis)
		recursive_exec(current->parenthesis, core);
	else
		ret_status = exec_ast_node(current->data, core);
	return (ret_status);
}

void	exec(t_core *core)
{
	t_cmd	*current;

	current = core->head;
	core->heredoc_counter = 1;
	recursive_exec(current, core);
	if (g_exit_status == 130)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (g_exit_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}
