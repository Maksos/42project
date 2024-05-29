/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:21:31 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:54:19 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_fill_with(char *s1, char *s2)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * PATH_MAX);
	if (new == NULL)
		return (NULL);
	while (s1 && *s1)
	{
		*(new + i) = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		*(new + i) = *s2;
		i++;
		s2++;
	}
	*(new + i) = '\0';
	return (new);
}

int	add_new_path_in_env(char *str, t_core *core, int f)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (core->env && core->env[++i])
		mem_list_chars(&tmp, core->env[i], core);
	mem_list_chars(&tmp, str, core);
	free_chars(core->env);
	core->env = t_list_to_strings(tmp);
	free_t_list(tmp, 1);
	if (f == 1 && str)
		free(str);
	if (core->env == NULL)
		return (-1);
	return (0);
}

int	find_and_replace_pwds(char *pwd, char *oldpwd, t_core *core)
{
	int	i;

	i = exist_in_env("PWD=", core);
	if (i >= 0)
	{
		free(core->env[i]);
		core->env[i] = ft_strdup(pwd);
		free(pwd);
	}
	else if (add_new_path_in_env(pwd, core, 0) != 0)
		return (-1);
	i = exist_in_env("OLDPWD=", core);
	if (i >= 0)
	{
		free(core->env[i]);
		core->env[i] = ft_strdup(oldpwd);
		free(oldpwd);
	}
	else if (add_new_path_in_env(oldpwd, core, 1) != 0)
		return (-1);
	return (0);
}

int	update_pwds(t_core *core)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;
	int		ret;

	tmp = NULL;
	pwd = NULL;
	oldpwd = NULL;
	tmp = get_env("PWD=", core);
	if (tmp == NULL)
		return (set_pwd(core));
	oldpwd = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	tmp = NULL;
	tmp = malloc(sizeof(char) * PATH_MAX);
	if (tmp == NULL)
		return (-1);
	getcwd(tmp, PATH_MAX);
	pwd = str_fill_with("PWD=", tmp);
	free(tmp);
	ret = find_and_replace_pwds(pwd, oldpwd, core);
	return (0);
}

int	go_to_new_path(char	*path_to_go, t_core *core)
{
	if (access(path_to_go, F_OK) == 0)
	{
		if (access(path_to_go, R_OK) == 0)
		{
			if (chdir(path_to_go) == -1)
				perror(strerror(errno));
			else
			{
				if (update_pwds(core) != 0)
					return (-1);
				return (0);
			}
		}
		else
			perror(strerror(errno));
	}
	else
		perror(strerror(errno));
	return (-2);
}
