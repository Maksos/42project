/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:42:12 by mastie            #+#    #+#             */
/*   Updated: 2023/10/27 01:24:35 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_parser(char *to_print)
{
	ft_putstr_fd("Error: syntax error near unexpected `", 2);
	ft_putstr_fd(to_print, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int	check_to_add(t_token *current, t_token *last_added, t_core *core)
{
	if (current->id == 0)
		return (words(last_added, current, core));
	else if (current->id == 1)
		return (lparen(last_added, current, core));
	else if (current->id == 2)
		return (rparen(last_added, current, core));
	else if (current->id == 3)
		return (and(last_added, current, core));
	else if (current->id == 4)
		return (or(last_added, current, core));
	else if (current->id == 5)
		return (less(last_added, current, core));
	else if (current->id == 6)
		return (dless(last_added, current, core));
	else if (current->id == 7)
		return (great(last_added, current, core));
	else if (current->id == 8)
		return (dgreat(last_added, current, core));
	else if (current->id == 9)
		return (pipes(last_added, current, core));
	return (-1);
}

int	last_check(t_token *last_added, t_core *core)
{
	if (last_added && (last_added->id != 0 && last_added->id != 2))
		return (error_parser(last_added->verbose));
	else if (last_added && (t_token *)core->token_list->content == last_added
		&& last_added->id == 2)
		return (error_parser(last_added->verbose));
	return (0);
}

int	parser(t_core *core)
{
	t_token	*last_added;
	t_list	*token_head;
	int		ret;

	token_head = core->token_list;
	last_added = NULL;
	while (token_head)
	{
		ret = check_to_add(((t_token *)token_head->content), last_added, core);
		{
			if (ret != 0)
			{
				if (ret == 130)
					return (-1);
				return (error_parser(
						((t_token *)token_head->content)->verbose));
			}
		}
		last_added = (t_token *)token_head->content;
		token_head = token_head->next;
	}
	return (last_check(last_added, core));
}
