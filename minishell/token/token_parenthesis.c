/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:50:30 by mastie            #+#    #+#             */
/*   Updated: 2023/09/07 17:18:52 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lparen(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (struct_to_ast(last_added, current, core));
	if (last_added->id == 3 || last_added->id == 4 || last_added->id == 1)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}

int	rparen(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (-1);
	if (last_added->id == 0 || last_added->id == 2)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}
