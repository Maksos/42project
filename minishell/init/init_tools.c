/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:28:48 by mastie            #+#    #+#             */
/*   Updated: 2023/10/23 12:06:01 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_and_dquotes(t_core *core)
{
	int	i;

	i = 0;
	while (core->input && *(core->input + i))
	{
		if (*(core->input + i) == '\'' || *(core->input + i) == '"')
			i = go_to_char(i, core);
		else
			i++;
		if (i == -1)
		{
			ft_error_exit("Need a closing quote or dquote\n", 0, core);
			return (-1);
		}
	}
	return (0);
}

void	reset(t_core *core)
{
	core->empty_str_removed = 0;
	if (core->token_list)
		ft_lstclear(&core->token_list, &free_token);
	if (core->input)
		free(core->input);
	core->input = NULL;
	core->token_list = NULL;
	if (core->head)
	{
		free_cmd(core->head);
		if (core->current_parenthesis)
			free_t_list(core->current_parenthesis, 0);
		core->current_parenthesis = NULL;
		core->head = NULL;
		core->current = NULL;
		core->current_data = NULL;
		core->parenthesis_parent = NULL;
	}
	signal_activation();
}

void	tty_ready(void)
{
	if (isatty(0) != 1)
		ft_putstr_fd("This TTY have a closed STDIN\n", 2);
	else
		ft_putstr_fd("This TTY have an open STDIN\n", 1);
	if (isatty(1) != 1)
		ft_putstr_fd("This TTY have a closed STDOUT\n", 2);
	else
		ft_putstr_fd("This TTY have an open STDOUT\n", 1);
	if (isatty(2) != 1)
		ft_putstr_fd("This TTY have a closed STDERR\n", 1);
	else
		ft_putstr_fd("This TTY have an open STDERR\n", 1);
}

void	input_control(t_core *core)
{
	if (quotes_and_dquotes(core) == 0 && parenthesis(core) == 0)
	{
		lexer(core);
		if (core->input)
		{
			free(core->input);
			core->input = NULL;
		}
		if (core->token_list)
		{
			signal_ignore();
			if (parser(core) == 0)
				exec(core);
		}
	}
	reset(core);
}
