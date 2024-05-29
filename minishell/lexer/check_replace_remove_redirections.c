/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_remove_redirections.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:33:14 by mastie            #+#    #+#             */
/*   Updated: 2023/11/07 12:15:07 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_content_redirections(t_outfiles *current, t_list *tmp, t_core *core)
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
	free(current->filename);
	current->filename = new;
	free_t_list(save, 1);
	return (0);
}

int	check_replace_remove_redirections(t_outfiles *current,
	t_list **wildcard_index, t_core *core)
{
	int					ret;
	t_list				*tmp_str;
	t_char_and_tlist	tmp;

	tmp_str = NULL;
	tmp.str = current->filename;
	tmp.tlst = &tmp_str;
	ret = check(current->filename);
	if (ret == 0)
		return (0);
	if (remove_q(tmp.str) == 1)
		ret = remove_quote_dquotes(tmp, wildcard_index, core);
	else if (replace(tmp.str) == 1)
		ret = replace_dollar(tmp, wildcard_index, core);
	else
		add_position_to_wildcards(current->filename, &tmp_str, wildcard_index);
	if (new_content_redirections(current, tmp_str, core) == -1)
		return (-1);
	return (ret);
}
