/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:08:28 by mastie            #+#    #+#             */
/*   Updated: 2023/10/17 04:33:51 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* CONVERT THE WORDS PARTS TO TOKEN */
t_token	*word_token(char *e_verbose, t_core *core)
{
	t_token	*n_token;

	n_token = NULL;
	n_token = malloc(sizeof(t_token));
	if (n_token == NULL)
		return (NULL);
	n_token->verbose = ft_strdup(e_verbose);
	n_token->id = 0;
	ft_lstadd_back(&core->token_list, ft_lstnew(n_token));
	return (n_token);
}

/*SPLIT THE ECTRACTED CHAR THEN CONVERT IT TO TOKENS*/
int	words_to_word_token(char *extracted, t_core *core)
{
	char	**splited_string;
	int		i;

	splited_string = ft_split_words(extracted);
	if (splited_string == NULL)
		return (-1);
	i = -1;
	while (splited_string[++i])
	{
		if (word_token(splited_string[i], core) == NULL)
		{
			free_chars(splited_string);
			return (-1);
		}
	}
	free_chars(splited_string);
	return (0);
}

int	words_to_token(int from, int to, t_core *core)
{
	char	*new;
	int		i;

	new = NULL;
	new = malloc(sizeof(char) * (to - from + 1));
	i = 0;
	if (new == NULL)
		return (-1);
	else
	{
		while (from < to)
		{
			new[i] = *(core->input + from);
			i++;
			from++;
		}
		new[i] = '\0';
		i = words_to_word_token(new, core);
		free(new);
		if (i == -1)
			return (-1);
	}
	return (0);
}

int	get_word(int i, t_core *core)
{
	while (*(core->input + i) && not_words(i, core) == 0)
	{
		if (*(core->input + i) && (*(core->input + i) == '"'
				|| *(core->input + i) == '\''))
			i = go_to_char(i, core);
		while (*(core->input + i) && (*(core->input + i) != '"'
				&& *(core->input + i) != '\'') && not_words(i, core) == 0)
			i++;
	}
	return (i);
}

/*	LEXER TOKEN PARTS */
void	lexer(t_core *core)
{
	int	i;
	int	l_words;

	i = 0;
	while (*(core->input + i))
	{
		while (*(core->input + i) && is_space(*(core->input + i)) == 0)
			i++;
		l_words = i;
		if (*(core->input + i) && not_words(i, core) == 0)
		{
			i = get_word(i, core);
			if (words_to_token(l_words, i, core) == -1)
				return (ft_error_exit("Memory allocation failed\n", 1, core));
		}
		else if (*(core->input + i) && not_words(i, core) == 1)
			i += move_to_words(i, core);
		if (i == -1)
			return (ft_error_exit("Memory allocation failed\n", 1, core));
	}
}
