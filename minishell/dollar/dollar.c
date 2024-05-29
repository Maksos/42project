/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:50:53 by mastie            #+#    #+#             */
/*   Updated: 2023/10/30 18:31:55 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_sequence(char *str, int j, char *ref)
{
	int	i;

	i = 0;
	if (!*(str + j + 1))
		return (0);
	while (*(ref + i))
	{
		if (*(str + j + 1) == *(ref + i))
			return (0);
		i++;
	}
	return (1);
}

int	replace_dollar_at(t_char_and_tlist tmp, int i, int in_q, t_core *core)
{
	int		ret;
	char	*find;

	ret = dollar_name_length(tmp.str, i);
	if (ret > 0 || (ret == 0 && *(tmp.str + i + 1) == '?'))
	{
		if (ret == 0)
			ret++;
		find = extract_name(tmp.str, (i + 1), ret);
		if (find == NULL)
			return (-1);
		if (exist_in_env(find, core) >= 0)
			adjust_tmp(ft_strlen(find), core->env[exist_in_env(find, core)],
				tmp.tlst, core);
		else if (ft_memcmp(find, "?", 2) == 0)
		{
			free(find);
			find = ft_itoa(g_exit_status);
			adjust_tmp(0, find, tmp.tlst, core);
		}
		free(find);
	}
	else if (in_q == 1 || no_sequence(tmp.str, i, "*=$,.:;[]{}?\\/%") == 0)
		mem_list_chars(tmp.tlst, &*(tmp.str + (i)), core);
	return (i + ret + 1);
}

int	remove_replace_dollar(t_char_and_tlist tmp, int i, t_core *core)
{
	char	c;

	c = *(tmp.str + (i++));
	while (*(tmp.str + i) && *(tmp.str + i) != c)
	{
		if (*(tmp.str + i) == '$')
			i = replace_dollar_at(tmp, i, 1, core);
		else
			mem_list_chars(tmp.tlst, &*(tmp.str + (i++)), core);
	}
	return (i + 1);
}

int	replace_dollar(t_char_and_tlist tmp, t_list **wildcards, t_core *core)
{
	int	i;

	i = 0;
	while (*(tmp.str + i))
	{
		if (*(tmp.str + i) == '$')
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
