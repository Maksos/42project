/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:46 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/27 17:45:09 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_frst_grp_in_pipe(t_cmd *current, int fd_pipe[2], t_core *core)
{
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		ft_perror_exit("Minishell ", errno, core);
	if (close(fd_pipe[0]) == -1)
		ft_perror_exit("Minishell ", errno, core);
	exec_ast_node(current->data, core);
	if (core->token_operator)
		free_token_operator(core);
	if (core->env)
		free_chars(core->env);
	if (close(fd_pipe[1]) == -1)
		ft_perror_exit("Minishell ", errno, core);
	reset(core);
	exit (g_exit_status);
}

void	exec_scnd_grp_in_pipe(t_cmd *current, int fd_pipe[2], t_core *core)
{
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		ft_perror_exit("Minishell ", errno, core);
	if (close(fd_pipe[1]) == -1)
		ft_perror_exit("Minishell ", errno, core);
	recursive_exec(current, core);
	if (core->token_operator)
		free_token_operator(core);
	if (core->env)
		free_chars(core->env);
	if (close(fd_pipe[0]) == -1)
		ft_perror_exit("Minishell ", errno, core);
	reset(core);
	exit (g_exit_status);
}

int	exec_node_pipe(t_cmd *current, t_core *core)
{
	pid_t	child1;
	pid_t	child2;
	int		fd_pipe[2];
	int		status_child1;
	int		status_child2;

	if (pipe(fd_pipe) == -1)
		ft_perror_exit("Minishell ", errno, core);
	child1 = fork();
	if (child1 == -1)
		ft_perror_exit("Minishell ", errno, core);
	if (child1 == 0)
		exec_frst_grp_in_pipe(current, fd_pipe, core);
	child2 = fork();
	if (child2 == -1)
		ft_perror_exit("Minishell ", errno, core);
	if (child2 == 0)
		exec_scnd_grp_in_pipe(current->pipes, fd_pipe, core);
	ft_close_fds(fd_pipe);
	waitpid(child1, &status_child1, 0);
	waitpid(child2, &status_child2, 0);
	if (WIFEXITED(status_child2))
		g_exit_status = WEXITSTATUS(status_child2);
	return (g_exit_status);
}
