/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:37:26 by mastie            #+#    #+#             */
/*   Updated: 2023/11/06 19:25:29 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_chars(char **chars)
{
	int		i;
	char	*tmp;

	i = 0;
	while (chars && chars[i])
	{
		tmp = chars[i];
		i++;
		free(tmp);
	}
	if (chars && chars != NULL)
		free(chars);
	chars = NULL;
}

void	free_t_list(t_list *list, int free_content)
{
	t_list	*to_free;

	while (list)
	{
		to_free = list;
		list = list->next;
		if (free_content == 1)
		{
			if (to_free->content)
				free(to_free->content);
		}
		free(to_free);
		to_free = NULL;
	}
}

void	free_token(void *content)
{
	t_token	*to_free;

	to_free = (t_token *)content;
	if (to_free->verbose)
		free(to_free->verbose);
	if (to_free)
		free(to_free);
}

void	free_token_operator(t_core *core)
{
	int		i;

	i = 0;
	while (core->token_operator && core->token_operator[i])
	{
		if (core->token_operator[i]->verbose)
			free(core->token_operator[i]->verbose);
		if (core->token_operator[i])
			free(core->token_operator[i]);
		i++;
	}
	if (core->token_operator)
		free(core->token_operator);
	core->token_operator = NULL;
}

void	free_content(t_content *data)
{
	if (data->redirections)
		free_redirections(data);
	if (data->arguments)
		ft_lstclear(&data->arguments, &free_arguments);
	if (data->redirections)
		free(data->redirections);
	if (data->arguments)
		free(data->arguments);
	if (data->std_fds)
		free(data->std_fds);
	if (data)
		free(data);
	data = NULL;
}
