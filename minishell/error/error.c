/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:47:17 by mastie            #+#    #+#             */
/*   Updated: 2023/09/14 17:02:19 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_exit(char *to_print, int exiting, t_core *core)
{
	if (to_print)
		ft_putstr_fd(to_print, STDERR_FILENO);
	reset(core);
	if (exiting == 0)
		return ;
	if (core->token_operator)
		free_token_operator(core);
	core->token_operator = NULL;
	if (core->env)
		free_chars(core->env);
	core->env = NULL;
	exit(EXIT_FAILURE);
}

void	ft_perror_exit(char *to_print, int exiting, t_core *core)
{
	perror(to_print);
	ft_error_exit(NULL, exiting, core);
}
