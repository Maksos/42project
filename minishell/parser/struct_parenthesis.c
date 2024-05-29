/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:45:36 by mastie            #+#    #+#             */
/*   Updated: 2023/06/01 15:46:57 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parenthes	*new_t_parenthes(int input_position, int position)
{
	t_parenthes	*new;

	new = malloc(sizeof(t_parenthes));
	if (new == NULL)
		return (NULL);
	new->added_in_position = position;
	new->position = input_position;
	return (new);
}

t_parenthesis	*new_t_parenthesis(int lparenthesis, int rparenthesis)
{
	t_parenthesis	*new;

	new = malloc(sizeof(t_parenthesis));
	if (new == NULL)
		return (NULL);
	new->lparen = lparenthesis;
	new->rparen = rparenthesis;
	return (new);
}
