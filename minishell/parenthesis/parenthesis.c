/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:52:40 by mastie            #+#    #+#             */
/*   Updated: 2023/10/19 16:45:49 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_to_char(int i, t_core *core)
{
	char	c;

	c = *(core->input + i);
	i++;
	while (*(core->input + i) && *(core->input + i) != c)
		i++;
	if (!*(core->input + i))
		return (-1);
	else if (c == *(core->input + i))
		return (i + 1);
	return (-1);
}

int	adding_parenthesis_positions(t_core *core)
{
	int		i;
	int		lposition;
	int		rposition;

	i = 0;
	lposition = 0;
	rposition = 0;
	while (core->input && *(core->input + i))
	{
		if (*(core->input + i) == '\'' || *(core->input + i) == '"')
			i = go_to_char(i, core);
		else if (*(core->input + i) == '(')
			ft_lstadd_back(&core->lparenthesis,
				ft_lstnew(new_t_parenthes(i++, ++lposition)));
		else if (*(core->input + i) == ')')
			ft_lstadd_back(&core->rparenthesis,
				ft_lstnew(new_t_parenthes(i++, ++rposition)));
		else
			i++;
	}
	return (0);
}

int	reset_parenthesis(t_core *core)
{
	if (core->rparenthesis)
		free_t_list(core->rparenthesis, 1);
	if (core->lparenthesis)
		free_t_list(core->lparenthesis, 1);
	core->rparenthesis = NULL;
	core->lparenthesis = NULL;
	printf("Error in parenthesis\n");
	return (-1);
}

int	parenthesis(t_core *core)
{
	if (adding_parenthesis_positions(core) == -1)
		return (reset_parenthesis(core));
	else if (ft_lstsize(core->lparenthesis) != ft_lstsize(core->rparenthesis))
		return (reset_parenthesis(core));
	checking_parenthesis(core);
	if (core->current_parenthesis)
		free_t_list(core->current_parenthesis, 1);
	core->current_parenthesis = NULL;
	if (core->rparenthesis || core->lparenthesis)
		return (reset_parenthesis(core));
	core->rparenthesis = NULL;
	core->lparenthesis = NULL;
	return (0);
}
