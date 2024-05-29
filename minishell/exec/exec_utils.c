/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:54:18 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/26 02:13:39 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_t_exec(t_execs *exec)
{
	exec->cmd = NULL;
	exec->args = NULL;
	exec->executables = NULL;
	exec->cmd_path = NULL;
}

char	**extract_path(char **env)
{
	char	**new;
	int		i;

	new = NULL;
	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			new = ft_split(env[i] + 5, ':');
		i++;
	}
	if (!new)
	{
		i = 0;
		while (env && env[i])
		{
			if (ft_strnstr(env[i], "_=", 2))
				new = ft_split(env[i] + 2, ':');
			i++;
		}
	}
	return (new);
}

char	**extract_args(t_list *cmd_args)
{
	char	**new;
	int		args_nb;

	args_nb = 0;
	args_nb = ft_lstsize(cmd_args);
	new = NULL;
	if (args_nb > 0)
	{
		new = malloc(sizeof(char *) * (args_nb + 1));
		if (new == NULL)
			return (NULL);
		args_nb = 0;
		while (cmd_args)
		{
			new[args_nb] = ft_strdup((char *)cmd_args->content);
			cmd_args = cmd_args->next;
			args_nb++;
		}
		new[args_nb] = NULL;
	}
	return (new);
}

int	is_cmd_absolute_path(char *executable)
{
	int	i;

	i = 0;
	if (!executable)
		return (0);
	while (executable[i])
	{
		if (executable[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ambiguous_redirection(t_outfiles *outfile)
{
	ft_putstr_fd(outfile->filename, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	g_exit_status = 1;
	return (1);
}
