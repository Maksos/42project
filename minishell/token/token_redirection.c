/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:39:50 by mastie            #+#    #+#             */
/*   Updated: 2023/11/07 16:10:38 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	less(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (struct_to_ast(last_added, current, core));
	else if (last_added->id == 0 || (last_added->id >= 3
			&& last_added->id <= 4) || last_added->id == 1
		|| last_added->id == 9)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}

int	dless(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (struct_to_ast(last_added, current, core));
	else if (last_added->id == 0 || (last_added->id >= 3
			&& last_added->id <= 4) || last_added->id == 1
		|| last_added->id == 9)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}

int	great(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (struct_to_ast(last_added, current, core));
	else if (last_added->id == 0 || (last_added->id >= 3
			&& last_added->id <= 4) || last_added->id == 1
		|| last_added->id == 9)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}

int	dgreat(t_token *last_added, t_token *current, t_core *core)
{
	if (!last_added)
		return (struct_to_ast(last_added, current, core));
	else if (last_added->id == 0 || (last_added->id >= 3
			&& last_added->id <= 4) || last_added->id == 1
		|| last_added->id == 9)
		return (struct_to_ast(last_added, current, core));
	return (-1);
}
