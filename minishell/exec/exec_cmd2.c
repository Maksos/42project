/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:57:47 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/29 23:52:01 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_for_path(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str1;
	char	*str2;
	char	*dest;

	str1 = (char *)s1;
	str2 = (char *)s2;
	len_s1 = ft_strlen(str1);
	len_s2 = ft_strlen(str2);
	dest = ft_calloc(sizeof(char), (len_s1 + len_s2 + 2));
	if (!dest)
		return (0);
	ft_strlcat(dest, str1, (len_s1 + 1));
	dest[len_s1] = '/';
	ft_strlcat(dest, str2, len_s1 + len_s2 + 2);
	return (dest);
}

char	*check_cmd_access(char **cmd_paths, char **cmd_args, t_core *core)
{
	int		i;
	char	*command;

	i = 0;
	while (cmd_paths && cmd_paths[i])
	{
		command = strjoin_for_path(cmd_paths[i], cmd_args[0]);
		if (!command)
			ft_error_exit("Memory allocation failed\n", ENOMEM, core);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

int	cmd_not_found(char *cmd)
{
	ft_putstr_fd("\'", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\'", STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

int	check_absolute_access(char *binary_path, int *found_bool)
{
	if (access(binary_path, F_OK))
		return (1);
	*found_bool = 1;
	if (access(binary_path, X_OK))
		return (1);
	return (0);
}

int	get_cmd_args_and_path(t_list *cmd_args, t_execs *exec, t_core *core)
{
	exec->cmd = ft_strdup((char *)cmd_args->content);
	exec->args = extract_args(cmd_args);
	if (!exec->args)
		ft_error_exit("Memory allocation failed\n", ENOMEM, core);
	if (is_cmd_absolute_path(exec->cmd))
	{
		exec->cmd_path = ft_strdup(exec->cmd);
		exec->executables = NULL;
	}
	else
	{
		if (exec->cmd && !*exec->cmd)
			g_exit_status = cmd_not_found(exec->cmd);
		else
		{
			exec->executables = extract_path(core->env);
			exec->cmd_path = check_cmd_access(exec->executables,
					exec->args, core);
			if (exec->cmd_path == NULL)
				g_exit_status = cmd_not_found(exec->cmd);
		}
	}
	return (g_exit_status);
}
