/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:56:06 by mastie            #+#    #+#             */
/*   Updated: 2023/10/07 17:43:13 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_globals(t_core *core)
{
	g_exit_status = 0;
	core->heredoc_counter = 1;
	core->arg_has_quotes = 0;
	core->empty_str_removed = 0;
	core->env = NULL;
	core->input = NULL;
	core->token_list = NULL;
	core->head = NULL;
	core->current = NULL;
	core->current_data = NULL;
	core->current_parenthesis = NULL;
	core->parenthesis_parent = NULL;
	core->rparenthesis = NULL;
	core->lparenthesis = NULL;
	core->token_operator = NULL;
}

t_token	*new_token_operator(char *str, int id, t_core *core)
{
	t_token	*new;

	new = NULL;
	new = malloc(sizeof(t_token));
	if (new == NULL)
		ft_error_exit("Memorry allocation failed\n", 1, core);
	new->verbose = NULL;
	new->id = id;
	if (str)
	{
		new->verbose = ft_strdup(str);
		if (new->verbose == NULL)
		{
			free(new);
			ft_error_exit("Memorry allocation failed\n", 1, core);
		}
	}
	return (new);
}

void	init_token_operator(t_core *core)
{
	int	i;

	i = -1;
	core->token_operator = malloc(sizeof(t_token *) * 11);
	if (!core->token_operator)
		ft_error_exit("Memorry allocation failed\n", 1, core);
	while (++i <= 10)
		core->token_operator[i] = NULL;
	core->token_operator[0] = new_token_operator("(", 1, core);
	core->token_operator[1] = new_token_operator(")", 2, core);
	core->token_operator[2] = new_token_operator("&&", 3, core);
	core->token_operator[3] = new_token_operator("||", 4, core);
	core->token_operator[4] = new_token_operator(">>", 8, core);
	core->token_operator[5] = new_token_operator("<<", 6, core);
	core->token_operator[6] = new_token_operator(">", 7, core);
	core->token_operator[7] = new_token_operator("<", 5, core);
	core->token_operator[8] = new_token_operator("|", 9, core);
	core->token_operator[9] = new_token_operator(NULL, 0, core);
	core->token_operator[10] = NULL;
}
