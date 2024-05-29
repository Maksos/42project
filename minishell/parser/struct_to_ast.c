/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:35:13 by mastie            #+#    #+#             */
/*   Updated: 2023/10/27 01:06:43 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_ast(t_core *core)
{
	core->head = new_t_cmd();
	if (core->head == NULL)
		return (-1);
	core->current = core->head;
	return (0);
}

int	struct_to_ast(t_token *last_added, t_token *current, t_core *core)
{
	int	ret;

	ret = 0;
	if (!last_added)
		ret = init_ast(core);
	if (ret == 0 && current->id == 0)
		ret = struct_to_ast_by_words(last_added, current, core);
	else if (ret == 0 && current->id == 1)
		ret = struct_to_ast_by_lparen(core);
	else if (ret == 0 && current->id == 2)
		ret = struct_to_ast_by_rparen(core);
	else if (ret == 0 && (current->id == 3 || current->id == 4))
		ret = struct_to_ast_by_and_or(current, core);
	else if (ret == 0 && current->id >= 5 && current->id <= 8)
		ret = struct_to_ast_by_redirections(core);
	else if (ret == 0 && current->id == 9)
		ret = struct_to_ast_by_pipe(core);
	if (ret == -1)
		ft_error_exit("Memory allocation failed\n", 1, core);
	return (ret);
}
