/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:00:18 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/07 16:27:02 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_empty_string_redirections(t_outfiles *tmp)
{
	char	*str;

	str = tmp->filename;
	if (str[0] == 0)
	{
		ft_putstr_fd("Minishell : ", STDERR_FILENO);
		ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	print_wc_redirection_error(char *filename, int size_lst)
{
	g_exit_status = 1;
	if (size_lst == 0)
	{
		ft_putstr_fd("Minishell : ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (size_lst > 1)
	{
		ft_putstr_fd("Minishell : ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	}
}

int	check_wildcards_in_redirection(t_list *tmp, t_list *files_from_wildcard,
	t_list **wildcard_index)
{
	int	size_lst;

	size_lst = ft_lstsize(files_from_wildcard);
	if (size_lst == 1)
	{
		free(((t_outfiles *)tmp->content)->filename);
		((t_outfiles *)tmp->content)->filename = files_from_wildcard->content;
	}
	else
	{
		print_wc_redirection_error(((t_outfiles *)tmp->content)->filename,
			size_lst);
		free_t_list(*wildcard_index, 1);
		*wildcard_index = NULL;
		free_t_list(files_from_wildcard, 1);
		return (1);
	}
	return (0);
}

int	expand_redirections(t_list *tmp, t_core *core)
{
	t_list	*wildcard_index;
	t_list	*files_from_wildcard;

	wildcard_index = NULL;
	while (tmp)
	{
		check_replace_remove_redirections(tmp->content, &wildcard_index, core);
		if (check_empty_string_redirections(tmp->content))
			return (1);
		if (wildcard_index)
		{
			files_from_wildcard = get_files_with_wildcard(((t_outfiles *)tmp
						->content)->filename, ".", wildcard_index, core);
			if (check_wildcards_in_redirection(tmp,
					files_from_wildcard, &wildcard_index))
				return (1);
			free_t_list(files_from_wildcard, 0);
			free_t_list(wildcard_index, 1);
			wildcard_index = NULL;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	expand_ast_node(t_content *data, t_core *core)
{
	if (data->redirections)
	{
		if (data->redirections->infiles)
		{
			if (expand_redirections(data->redirections->infiles, core))
				return (1);
		}
		if (data->redirections->outfiles)
		{
			if (expand_redirections(data->redirections->outfiles, core))
				return (1);
		}
	}
	if (data->arguments)
		expand_arguments(data, core);
	return (0);
}
