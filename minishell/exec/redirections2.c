/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:19:16 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/18 19:35:24 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirections_and_store_standard_fds(t_content *data, t_core *core)
{
	data->std_fds = malloc(sizeof(t_std_fds));
	if (!data->std_fds)
		ft_error_exit("Memory allocation failed\n", ENOMEM, core);
	data->std_fds->original_stdin = -1;
	data->std_fds->original_stdout = -1;
	data->std_fds->new_stdin = -1;
	data->std_fds->new_stdout = -1;
	if (redirecting(data, core))
		return (g_exit_status);
	return (0);
}

void	flush_fds(t_std_fds *std_fds, t_core *core)
{
	if (std_fds->original_stdin >= 0 && std_fds->new_stdin >= 0)
	{
		if (dup2(std_fds->original_stdin, STDIN_FILENO) == -1)
			ft_error_exit("dup2 failed\n", errno, core);
		if (close(std_fds->original_stdin) == -1)
			ft_error_exit("Close fd failed\n", errno, core);
	}
	if (std_fds->original_stdout >= 0 && std_fds->new_stdout >= 0)
	{
		if (dup2(std_fds->original_stdout, STDOUT_FILENO) == -1)
			ft_error_exit("dup2 failed\n", errno, core);
		if (close(std_fds->original_stdout) == -1)
			ft_error_exit("Close fd failed\n", errno, core);
	}
}
