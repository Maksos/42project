/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:54:33 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/07 12:22:18 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_and_exec_cmd(t_content *data, t_execs exec,
	t_core *core)
{
	signal_default();
	if (data->redirections)
	{
		if (handle_redirections(data, core))
			return (redirections_error_handler(core, exec));
	}
	if (data->arguments)
	{
		if (execve(exec.cmd_path, exec.args, core->env) == -1)
			return (execve_error_handler(core, exec));
	}
	free_exec(exec);
	if (core->token_operator)
		free_token_operator(core);
	if (core->env)
		free_chars(core->env);
	reset(core);
	return (0);
}

int	check_if_builtin(t_content *data, t_execs *exec, t_core *core)
{
	if (data->arguments)
	{
		if (is_a_builtin((char *)data->arguments->content) == 0)
		{
			g_exit_status = builtins_call(data, core);
			if (data->redirections)
				flush_fds(data->std_fds, core);
			return (1);
		}
		else
		{
			g_exit_status = 0;
			return (get_cmd_args_and_path(data->arguments, exec, core));
		}
	}
	return (0);
}

int	exec_ast_node(t_content *data, t_core *core)
{
	t_execs		exec;
	pid_t		child;
	int			status_child;

	status_child = -1;
	if (expand_ast_node(data, core))
		return (1);
	init_t_exec(&exec);
	if (check_if_builtin(data, &exec, core))
	{
		free_exec(exec);
		return (g_exit_status);
	}
	child = fork();
	if (child == -1)
		ft_error_exit("Fork failed\n", errno, core);
	if (child == 0)
		exit(redirect_and_exec_cmd(data, exec, core));
	waitpid(child, &status_child, 0);
	free_exec(exec);
	if (WIFSIGNALED(status_child))
		g_exit_status = 128 + WTERMSIG(status_child);
	else
		g_exit_status = WEXITSTATUS(status_child);
	return (g_exit_status);
}
