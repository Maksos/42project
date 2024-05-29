/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_remove.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:33:14 by mastie            #+#    #+#             */
/*   Updated: 2023/11/04 19:35:23 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '"' || *(str + i) == '\'')
			return (1);
		else if (*(str + i) == '$')
			return (2);
		else if (*(str + i) == '*')
			return (3);
		i++;
	}
	return (0);
}

int	replace(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '$' && *(str + i + 1) && sep_dollar(*(str + i + 1),
				"+-\n\f\v\r\t %=$,.:;[]{}\'\\\"/") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	new_content(t_list *current, t_list *tmp, t_core *core)
{
	char	*new;
	t_list	*save;
	int		i;

	new = malloc(sizeof(char) * (ft_lstsize(tmp) + 1));
	if (new == NULL)
		ft_perror_exit("Minishell ", errno, core);
	i = 0;
	save = tmp;
	while (tmp)
	{
		new[i] = *((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	new[i] = '\0';
	free(current->content);
	current->content = new;
	free_t_list(save, 1);
}

void	add_position_to_wildcards(char *str, t_list **tmp,
	t_list **wildcard_index)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '*')
			ft_lstadd_back(wildcard_index,
				ft_lstnew(new_t_wildcards(ft_lstsize(*tmp))));
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup(&*(str + (i++)))));
	}
}

void	check_replace_remove(t_list *current, t_list **wc_i, t_core *core)
{
	t_list				*tmp_str;
	t_char_and_tlist	tmp;

	tmp_str = NULL;
	tmp.str = current->content;
	tmp.tlst = &tmp_str;
	if (check(current->content) == 0)
		return ;
	core->arg_has_quotes = 0;
	if (remove_q(current->content) == 1)
	{
		core->arg_has_quotes = 1;
		remove_quote_dquotes(tmp, wc_i, core);
	}
	else if (replace(current->content) == 1)
		replace_dollar(tmp, wc_i, core);
	else
		add_position_to_wildcards(current->content, &tmp_str, wc_i);
	if (check_replace_dollar_space(current, *tmp.tlst) == 0
		&& core->arg_has_quotes != 1)
		replace_space_by_args(current, *tmp.tlst, core);
	else
		new_content(current, tmp_str, core);
}
