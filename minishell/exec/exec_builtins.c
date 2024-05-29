/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:46:37 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:33:48 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_a_builtin(char *cmd)
{
	int	ret;

	ret = -1;
	if (ft_memcmp(cmd, "env", 4) == 0)
		ret = 0;
	else if (ft_memcmp(cmd, "unset", 6) == 0)
		ret = 0;
	else if (ft_memcmp(cmd, "export", 7) == 0)
		ret = 0;
	else if (ft_memcmp(cmd, "echo", 5) == 0)
		ret = 0;
	else if (ft_memcmp(cmd, "exit", 5) == 0)
		ret = 0;
	else if (ft_memcmp(cmd, "cd", 3) == 0)
		ret = 0;
	else if (ft_memcmp(cmd, "pwd", 4) == 0)
		ret = 0;
	return (ret);
}

int	builtins_call(t_content *data, t_core *core)
{
	char	*cmd;

	cmd = (char *)data->arguments->content;
	if (data->redirections)
	{
		if (handle_redirections_and_store_standard_fds(data, core))
			return (g_exit_status);
	}
	if (ft_memcmp(cmd, "env", 4) == 0)
		return (ft_env(data, core));
	else if (ft_memcmp(cmd, "unset", 6) == 0)
		return (ft_unset(data, core));
	else if (ft_memcmp(cmd, "export", 7) == 0)
		return (ft_export(data, core));
	else if (ft_memcmp(cmd, "echo", 5) == 0)
		return (ft_echo(data));
	else if (ft_memcmp(cmd, "cd", 3) == 0)
		return (ft_cd(data, core));
	else if (ft_memcmp(cmd, "pwd", 4) == 0)
		return (ft_pwd(data, core));
	else if (ft_memcmp(cmd, "exit", 5) == 0)
		ft_exit(data, core);
	return (g_exit_status);
}
