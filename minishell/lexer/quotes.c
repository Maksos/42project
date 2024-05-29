/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:54:06 by mastie            #+#    #+#             */
/*   Updated: 2023/10/19 16:49:55 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_q(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '"' || *(str + i) == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	fill_until_close_q(char *str, int i, t_list **tmp, t_core *core)
{
	char	c;

	c = *(str + (i++));
	while (*(str + i) && *(str + i) != c)
		mem_list_chars(tmp, &*(str + (i++)), core);
	return (i + 1);
}

int	remove_quote_dquotes(t_char_and_tlist tmp, t_list **wildcards, t_core *core)
{
	int	i;

	i = 0;
	while (*(tmp.str + i))
	{
		if (*(tmp.str + i) == '"')
			i = remove_replace_dollar(tmp, i, core);
		else if (*(tmp.str + i) == '\'')
			i = fill_until_close_q(tmp.str, i, tmp.tlst, core);
		else if (*(tmp.str + i) == '$')
			i = replace_dollar_at(tmp, i, 0, core);
		else
		{
			if (*(tmp.str + i) == '*')
				ft_lstadd_back(wildcards,
					ft_lstnew(new_t_wildcards(ft_lstsize(*tmp.tlst))));
			ft_lstadd_back(tmp.tlst, ft_lstnew(ft_strdup(&*(tmp.str + (i++)))));
		}
		if (i == -1)
			return (-1);
	}
	return (0);
}
