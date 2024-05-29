/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:42:19 by mastie            #+#    #+#             */
/*   Updated: 2023/11/07 12:44:22 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arguments(void *content)
{
	if (content)
		free((char *)content);
	content = NULL;
}

void	free_outfiles(void *content)
{
	t_outfiles	*tmp;

	tmp = content;
	if (tmp)
	{
		if (tmp->filename)
			free(tmp->filename);
		free(tmp);
	}
}

void	free_redirections(t_content *data)
{
	if (data->redirections->infiles)
		ft_lstclear(&(data->redirections->infiles), &free_outfiles);
	if (data->redirections->outfiles)
		ft_lstclear(&(data->redirections->outfiles), &free_outfiles);
}

void	free_cmd(t_cmd *command)
{
	if (command && command->parenthesis)
		free_cmd(command->parenthesis);
	if (command && command->and)
		free_cmd(command->and);
	if (command && command->or)
		free_cmd(command->or);
	if (command && command->pipes)
		free_cmd(command->pipes);
	if (command && command->data)
		free_content(command->data);
	if (command)
		free(command);
}
