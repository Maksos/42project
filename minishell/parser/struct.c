/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:08:25 by mastie            #+#    #+#             */
/*   Updated: 2023/05/29 19:34:04 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_wildcards	*new_t_wildcards(int position)
{
	t_wildcards	*new;

	new = malloc(sizeof(t_wildcards));
	if (new == NULL)
		return (NULL);
	new->position = position;
	return (new);
}

t_content	*new_t_content(void)
{
	t_content	*new;

	new = malloc(sizeof(t_content));
	if (new == NULL)
		return (NULL);
	new->arguments = NULL;
	new->redirections = NULL;
	new->std_fds = NULL;
	return (new);
}

t_cmd	*new_t_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->data = NULL;
	new->and = NULL;
	new->or = NULL;
	new->pipes = NULL;
	new->parenthesis = NULL;
	return (new);
}
