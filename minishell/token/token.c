/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:54:15 by mastie            #+#    #+#             */
/*   Updated: 2023/09/07 17:30:12 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	words(t_token *last_added, t_token *current, t_core *core)
{
	if (last_added && last_added->id == 2)
		return (-1);
	return (struct_to_ast(last_added, current, core));
}
