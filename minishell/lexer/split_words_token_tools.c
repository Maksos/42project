/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_token_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:39:46 by mastie            #+#    #+#             */
/*   Updated: 2023/06/15 21:14:30 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_to_char_filling(const char *s, int i, int start, char *new)
{
	char	c;

	c = *(s + start + i);
	new[i] = *(s + start + i);
	i++;
	while (*(s + start + i) && *(s + start + i) != c)
	{
		new[i] = *(s + start + i);
		i++;
	}
	new[i] = *(s + start + i);
	i++;
	return (i);
}

char	*fill_extracted_line_token(char const *s, int start, char *new)
{
	int		i;

	i = 0;
	while (*(s + start + i) && is_spaced(*(s + start + i)) == 0)
	{
		if (*(s + start + i) == '\'' || *(s + start + i) == '"')
			i = go_to_char_filling(s, i, start, new);
		else if (*(s + start + i))
		{
			new[i] = *(s + start + i);
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}

char	*extract_line_token(char const *s, int start)
{
	char	*new;
	int		i;

	i = 0;
	while (*(s + start + i) && is_spaced(*(s + start + i)) == 0)
	{
		if (*(s + start + i) == '\'' || *(s + start + i) == '"')
			i = go_to_char_split(s, start + i) - start;
		else
			i++;
	}
	new = malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	new = fill_extracted_line_token(s, start, new);
	return (new);
}
