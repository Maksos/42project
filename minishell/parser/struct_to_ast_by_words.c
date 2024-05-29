/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_ast_by_words.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:43:29 by mastie            #+#    #+#             */
/*   Updated: 2023/11/04 19:40:15 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_to_ast_by_id(t_token *last_added, t_token *current, t_core *core)
{
	int	ret;

	ret = g_exit_status;
	if (last_added->id == 5)
		ft_lstadd_back(&(core->current_data->redirections->infiles),
			ft_lstnew(new_t_outfiles(last_added->id, current->verbose, core)));
	else if (last_added->id == 6)
	{
		ft_lstadd_back(&(core->current_data->redirections->infiles),
			ft_lstnew(new_heredoc_t_outfiles(
					get_heredoc_tmp_filename(current->verbose, core))));
		if (g_exit_status == 130)
			return (130);
		else
			g_exit_status = ret;
	}
	else if (last_added->id == 7 || last_added->id == 8)
		ft_lstadd_back(&(core->current_data->redirections->outfiles),
			ft_lstnew(new_t_outfiles(last_added->id, current->verbose, core)));
	else
		ft_lstadd_back(&(core->current_data->arguments),
			ft_lstnew(ft_strdup(current->verbose)));
	return (0);
}

int	struct_to_ast_by_words(t_token *last_added, t_token *current, t_core *core)
{
	if (!core->current->data && !core->current_data)
	{
		core->current->data = new_t_content();
		if (core->current->data == NULL)
			return (-1);
		core->current_data = core->current->data;
	}
	if (!last_added)
	{
		ft_lstadd_back(&core->current_data->arguments,
			ft_lstnew(ft_strdup(current->verbose)));
		return (0);
	}
	return (word_to_ast_by_id(last_added, current, core));
}
