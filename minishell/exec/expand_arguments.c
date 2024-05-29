/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:46:45 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/30 18:58:43 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_empty_string_args(t_list **tmp, t_list *tmp_previous,
	t_content *data, t_core *core)
{
	char	*str;

	str = (*tmp)->content;
	if (str[0] == 0)
	{
		core->empty_str_removed = 1;
		if (tmp_previous)
		{
			tmp_previous->next = (*tmp)->next;
			free((*tmp)->content);
			free(*tmp);
			*tmp = tmp_previous;
		}
		else
		{
			data->arguments = (*tmp)->next;
			free((*tmp)->content);
			free(*tmp);
			*tmp = data->arguments;
		}
		*tmp = tmp_previous;
	}
}

void	insert_wildcards(t_tmp_tlist *tmp, t_content *data, t_core *core)
{
	tmp->files_from_wildcard = get_files_with_wildcard(tmp->current->content,
			".", tmp->wildcard_index, core);
	if (tmp->files_from_wildcard)
	{
		if (!(tmp->previous))
			data->arguments = tmp->files_from_wildcard;
		else
			tmp->previous->next = tmp->files_from_wildcard;
		tmp->previous = ft_lstlast(tmp->files_from_wildcard);
		tmp->previous->next = tmp->next;
		free(tmp->current->content);
		free(tmp->current);
	}
	else
		tmp->previous = tmp->current;
}

void	expand_arguments(t_content *data, t_core *core)
{
	t_tmp_tlist	tmp;

	tmp.previous = NULL;
	tmp.wildcard_index = NULL;
	tmp.current = data->arguments;
	while (tmp.current)
	{
		tmp.next = tmp.current->next;
		check_replace_remove(tmp.current, &tmp.wildcard_index, core);
		if (core->arg_has_quotes == 0)
			check_empty_string_args(&tmp.current, tmp.previous, data, core);
		if (tmp.wildcard_index)
		{
			insert_wildcards(&tmp, data, core);
			free_t_list(tmp.wildcard_index, 1);
			tmp.wildcard_index = NULL;
		}
		else
			tmp.previous = tmp.current;
		tmp.current = tmp.next;
	}
}

int	is_path_a_directory(char *cmd_path)
{
	struct stat	stat_buf;

	if (stat(cmd_path, &stat_buf) != 0)
	{
		perror("stat ");
		return (0);
	}
	return (S_ISDIR(stat_buf.st_mode));
}

void	check_exec_error(char *cmd_path)
{
	if (is_path_a_directory(cmd_path))
	{
		ft_putstr_fd("Minishell : ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("Minishell : ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
}
