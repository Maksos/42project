/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_in_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:57 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/07 12:46:44 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec(t_execs exec)
{
	if (exec.cmd)
		free(exec.cmd);
	if (exec.args)
		free_chars(exec.args);
	if (exec.cmd_path)
		free(exec.cmd_path);
	if (exec.executables)
		free_chars(exec.executables);
}

int	execve_error_handler(t_core *core, t_execs exec)
{
	if (errno == 13)
	{
		check_exec_error(exec.cmd_path);
		free_exec(exec);
		if (core->token_operator)
			free_token_operator(core);
		if (core->env)
			free_chars(core->env);
		reset(core);
		return (126);
	}
	else
	{
		ft_putstr_fd("Minishell : ", STDERR_FILENO);
		ft_putstr_fd(exec.cmd_path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_exec(exec);
		if (core->token_operator)
			free_token_operator(core);
		if (core->env)
			free_chars(core->env);
		reset(core);
		return (127);
	}
}

int	redirections_error_handler(t_core *core, t_execs exec)
{
	free_exec(exec);
	if (core->token_operator)
		free_token_operator(core);
	if (core->env)
		free_chars(core->env);
	reset(core);
	return (1);
}
