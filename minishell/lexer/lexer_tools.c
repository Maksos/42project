/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:05:22 by mastie            #+#    #+#             */
/*   Updated: 2023/09/05 17:55:40 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (0);
	return (1);
}

/* CHECK IF THE *CHAR IS IN THE LIST; SPECIAL CASE FOR '(' ET ')'  */
int	s_in(char *str, char *in, int pos)
{
	int		i;

	i = 0;
	if (*in == '(' || *in == ')')
		return (0);
	while (*(str + i + pos) && (*(str + i + pos) == *(in + i)))
		i++;
	if (!*(in + i))
		return (0);
	return (1);
}

/* CHECK IF THE CHAR IS IN THE TOKEN*/
int	not_words(int i, t_core *core)
{
	int	j;
	int	ret;

	ret = -1;
	if (*(core->input + i))
	{
		j = -1;
		while (core->token_operator[++j]->verbose)
		{
			if (*(core->input + i) == *(core->token_operator[j])->verbose)
				ret = s_in(core->input, core->token_operator[j]->verbose, i);
			if (ret == 0)
				return (1);
		}
	}
	return (0);
}

/* MOVE TO THE NEXT CHAR THAT IS NOT IN THE TOKEN SEPARATOR */
int	move_to_words(int i, t_core *core)
{
	t_token	*n_token;
	int		j;
	int		ret;

	j = -1;
	ret = -1;
	n_token = malloc(sizeof(t_token));
	if (n_token == NULL)
		return (-1);
	while (core->token_operator[++j]->verbose)
	{
		if (*(core->input + i) == *(core->token_operator[j])->verbose)
			ret = s_in(core->input, core->token_operator[j]->verbose, i);
		if (ret == 0)
		{
			n_token->verbose = ft_strdup(core->token_operator[j]->verbose);
			n_token->id = core->token_operator[j]->id;
			ft_lstadd_back(&core->token_list, ft_lstnew(n_token));
			i = ft_strlen(core->token_operator[j]->verbose);
			return (i);
		}
	}
	return (0);
}
