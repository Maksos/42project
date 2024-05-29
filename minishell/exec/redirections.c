/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:17:32 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/07 12:23:09 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_open(t_outfiles *tmp_outfiles, t_std_fds *std_fds, int in_or_out)
{
	if (in_or_out == 1)
	{
		if (std_fds->new_stdout == -1)
		{
			ft_putstr_fd(tmp_outfiles->filename, STDERR_FILENO);
			perror(" ");
			g_exit_status = errno;
			return (g_exit_status);
		}
	}
	else
	{
		if (std_fds->new_stdin == -1)
		{
			ft_putstr_fd(tmp_outfiles->filename, STDERR_FILENO);
			perror(" ");
			g_exit_status = errno;
			return (g_exit_status);
		}
	}
	return (0);
}

int	handle_infiles(t_std_fds *std_fds, t_list *infiles, t_core *core)
{
	t_outfiles	*tmp_outfiles;

	while (infiles)
	{
		tmp_outfiles = infiles->content;
		if (std_fds->new_stdin != -1)
		{
			if (close(std_fds->new_stdin) == -1)
				ft_error_exit("Close failed\n", errno, core);
		}
		std_fds->new_stdin = open((char *)tmp_outfiles->filename, O_RDONLY);
		if (check_open(tmp_outfiles, std_fds, 0) != 0)
			return (g_exit_status);
		infiles = infiles->next;
	}
	if (dup2(std_fds->new_stdin, STDIN_FILENO) == -1)
		ft_error_exit("dup2 failed\n", errno, core);
	if (close(std_fds->new_stdin) == -1)
		ft_error_exit("Close fd failed\n", errno, core);
	return (0);
}

int	handle_outfiles(t_std_fds *std_fds, t_list *outfiles, t_core *core)
{
	t_outfiles	*tmp_outfiles;

	while (outfiles)
	{
		tmp_outfiles = outfiles->content;
		if (std_fds->new_stdout != -1)
		{
			if (close(std_fds->new_stdout) == -1)
				ft_error_exit("Close fd failed\n", errno, core);
		}
		std_fds->new_stdout = open((char *)tmp_outfiles->filename,
				O_WRONLY | O_CREAT | tmp_outfiles->open_flag, 0644);
		if (check_open(tmp_outfiles, std_fds, 1) != 0)
			return (g_exit_status);
		outfiles = outfiles->next;
	}
	if (dup2(std_fds->new_stdout, STDOUT_FILENO) == -1)
		ft_error_exit("dup2 failed\n", errno, core);
	if (close(std_fds->new_stdout) == -1)
		ft_error_exit("Close fd failed\n", errno, core);
	return (0);
}

int	handle_redirections(t_content *data, t_core *core)
{
	data->std_fds = malloc(sizeof(t_std_fds));
	if (!data->std_fds)
		ft_error_exit("Memory allocation failed\n", ENOMEM, core);
	data->std_fds->original_stdin = -1;
	data->std_fds->original_stdout = -1;
	data->std_fds->new_stdin = -1;
	data->std_fds->new_stdout = -1;
	if (data->redirections->infiles)
	{
		if (handle_infiles(data->std_fds, data->redirections->infiles, core))
			return (g_exit_status);
	}
	if (data->redirections->outfiles)
	{
		if (handle_outfiles(data->std_fds, data->redirections->outfiles, core))
			return (g_exit_status);
	}
	return (0);
}

int	redirecting(t_content *data, t_core *core)
{
	if (data->redirections->infiles)
	{
		data->std_fds->original_stdin = dup(STDIN_FILENO);
		if (data->std_fds->original_stdin == -1)
			ft_error_exit("dup failed\n", errno, core);
		if (handle_infiles(data->std_fds, data->redirections->infiles, core))
		{
			if (close(data->std_fds->original_stdin) == -1)
				ft_error_exit("Close fd failed\n", errno, core);
			return (g_exit_status);
		}
	}
	if (data->redirections->outfiles)
	{
		data->std_fds->original_stdout = dup(STDOUT_FILENO);
		if (data->std_fds->original_stdout == -1)
			ft_error_exit("dup failed\n", errno, core);
		if (handle_outfiles(data->std_fds, data->redirections->outfiles, core))
		{
			if (close(data->std_fds->original_stdout) == -1)
				ft_error_exit("Close fd failed\n", errno, core);
			return (g_exit_status);
		}
	}
	return (0);
}
