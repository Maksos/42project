/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:48:41 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:34:30 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_check_value(char *str)
{
	int	i;

	i = 0;
	if (*(str) == '-' || *(str) == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	check_or_convert(char *str)
{
	if (exit_check_value(str) == 0)
		return (0);
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" : numeric argument required\n", STDERR_FILENO);
	}
	return (-1);
}

void	ft_exit_free_core(t_core *core)
{
	if (core->env)
		free_chars(core->env);
	core->env = NULL;
	if (core->input)
		free(core->input);
	if (core->token_list)
		ft_lstclear(&core->token_list, &free_token);
	if (core->head)
		free_cmd(core->head);
	free_token_operator(core);
}

void	ft_exit(t_content *data, t_core *core)
{
	int	status;

	status = 0;
	if (data->arguments->next)
	{
		if (data->arguments->next->next)
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return ;
		}
		if (check_or_convert((char *)data->arguments->next->content) == 0)
			status = ft_atoi((char *)data->arguments->next->content);
		else
			return ;
	}
	ft_exit_free_core(core);
	g_exit_status = status;
	exit(status);
}
