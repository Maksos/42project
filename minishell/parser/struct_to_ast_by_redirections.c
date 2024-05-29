/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_to_ast_by_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:48:37 by mastie            #+#    #+#             */
/*   Updated: 2023/10/17 05:37:33 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirections	*new_t_redirections(void)
{
	t_redirections	*new;

	new = malloc(sizeof(t_redirections));
	if (new == NULL)
		return (NULL);
	new->infiles = NULL;
	new->outfiles = NULL;
	return (new);
}

t_outfiles	*new_heredoc_t_outfiles(char *verbose)
{
	t_outfiles	*new;

	new = malloc(sizeof(t_outfiles));
	if (new == NULL)
		return (NULL);
	new->open_flag = 0;
	new->filename = verbose;
	return (new);
}

t_outfiles	*new_t_outfiles(t_token_id id, char *verbose, t_core *core)
{
	t_outfiles	*new;

	new = malloc(sizeof(t_outfiles));
	if (new == NULL)
		return (NULL);
	if (id == 7)
		new->open_flag = O_TRUNC;
	else if (id == 8)
		new->open_flag = O_APPEND;
	else
		new->open_flag = 0;
	new->filename = ft_strdup(verbose);
	if (new->filename == NULL)
		ft_perror_exit("Minishell :", errno, core);
	return (new);
}

int	struct_to_ast_by_redirections(t_core *core)
{
	if (!core->current->data && !core->current_data)
	{
		core->current->data = new_t_content();
		if (core->current->data == NULL)
			return (-1);
		core->current_data = core->current->data;
	}
	if (!core->current_data->redirections)
	{
		core->current_data->redirections = new_t_redirections();
		if (core->current_data->redirections == NULL)
			return (-1);
	}
	return (0);
}
