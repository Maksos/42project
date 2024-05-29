/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:40:50 by mastie            #+#    #+#             */
/*   Updated: 2023/09/07 17:18:14 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	and(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (-1);
	if (last_added->id == 2 || last_added->id == 0)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}

int	or(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (-1);
	if (last_added->id == 2 || last_added->id == 0)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}

int	pipes(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (-1);
	if (last_added->id == 0)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}
