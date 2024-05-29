/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:14:31 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:32:59 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_option(t_list *argument)
{
	char	*str;

	if (argument)
	{
		str = (char *)argument->content;
		if (str && *str == '-')
		{
			ft_putstr_fd("pwd: `-", STDERR_FILENO);
			ft_putchar_fd(*(str + 1), STDERR_FILENO);
			ft_putstr_fd("': pwd invalid option\n", STDERR_FILENO);
			return (-1);
		}
	}
	return (0);
}

int	ft_pwd(t_content *data, t_core *core)
{
	char	*tmp_getcwd;

	tmp_getcwd = NULL;
	if (no_option(data->arguments->next) == -1)
		return (-1);
	tmp_getcwd = malloc(sizeof(char) * PATH_MAX);
	if (tmp_getcwd == NULL)
		ft_error_exit("Memory allocation failed", 1, core);
	if (getcwd(tmp_getcwd, PATH_MAX) == NULL)
	{
		free(tmp_getcwd);
		return (-1);
	}
	else
	{
		printf("%s\n", tmp_getcwd);
		free(tmp_getcwd);
		tmp_getcwd = NULL;
	}
	return (0);
}
