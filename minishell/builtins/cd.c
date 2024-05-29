/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:14:15 by mastie            #+#    #+#             */
/*   Updated: 2023/11/07 15:56:45 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_pwd(t_core *core)
{
	char	*tmp_getcwd;
	char	*new_pwd;
	int		ret;

	tmp_getcwd = NULL;
	new_pwd = NULL;
	tmp_getcwd = malloc(sizeof(char) * PATH_MAX);
	if (tmp_getcwd == NULL)
		ft_error_exit("Memory allocation failed", 1, core);
	if (getcwd(tmp_getcwd, PATH_MAX) == NULL)
	{
		free(tmp_getcwd);
		return (-1);
	}
	new_pwd = ft_strjoin("PWD=", tmp_getcwd);
	free(tmp_getcwd);
	ret = add_new_path_in_env(new_pwd, core, 1);
	return (ret);
}

int	go_to_old(t_core *core)
{
	char	*new_path;
	int		ret;

	new_path = get_env("OLDPWD=", core);
	if (!new_path)
	{
		ft_putstr_fd("OLDPWD NOT SET\n", STDERR_FILENO);
		return (2);
	}
	ret = go_to_new_path(new_path, core);
	if (ret == -1)
		ft_putstr_fd("Memory allocation failed\n", STDERR_FILENO);
	free(new_path);
	return (ret);
}

int	go_to_home(t_core *core)
{
	char	*new_path;
	int		ret;

	new_path = get_env("HOME=", core);
	if (!new_path || (new_path && !*new_path))
	{
		ft_putstr_fd("HOME not set or empty\n", STDERR_FILENO);
		return (-1);
	}
	ret = go_to_new_path(new_path, core);
	if (ret == -1)
		ft_putstr_fd("Memory allocation failed 2\n", STDERR_FILENO);
	free(new_path);
	return (ret);
}

int	try_to_go_to(t_list *tmp, t_core *core)
{
	int	ret;

	ret = -1;
	if (ft_memcmp((char *)tmp->content, "-", 2) == 0)
		ret = go_to_old(core);
	else
	{
		ret = go_to_new_path((char *)tmp->content, core);
		if (ret == -1)
			ft_putstr_fd("Memory allocation failed 3\n", STDERR_FILENO);
	}
	return (ret);
}

int	ft_cd(t_content *data, t_core *core)
{
	t_list	*tmp;
	int		ret;

	tmp = data->arguments->next;
	ret = -1;
	if (!tmp)
		ret = go_to_home(core);
	else if (tmp->next)
	{
		ft_putstr_fd("cd : too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if ((char *)tmp->content && *(char *)tmp->content)
		ret = try_to_go_to(tmp, core);
	return (ret);
}
