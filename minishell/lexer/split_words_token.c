/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:59:27 by mastie            #+#    #+#             */
/*   Updated: 2023/04/12 13:59:28 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

int	is_spaced(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	go_to_char_split(const char *s, int i)
{
	char	c;

	c = *(s + i);
	i++;
	while (*(s + i) && *(s + i) != c)
		i++;
	if (!*(s + i))
		return (-1);
	else if (c == *(s + i))
		return (i + 1);
	return (-1);
}

static char	**fill_tab(char **tab, char const *s)
{
	int	i;
	int	o;

	i = 0;
	o = -1;
	while (*(s + i))
	{
		while (*(s + i) && is_spaced(*(s + i)) == 1)
			i++;
		if (*(s + i) && is_spaced(*(s + i)) == 0)
		{
			tab[++o] = extract_line_token(s, i);
			if (tab[o] == NULL)
				return (free_tab(tab));
		}
		while (*(s + i) && is_spaced(*(s + i)) == 0)
		{
			if (*(s + i) == '\'' || *(s + i) == '"')
				i = go_to_char_split(s, i);
			else
				i++;
		}
	}
	tab[++o] = NULL;
	return (tab);
}

char	**ft_split_words(char const *s)
{
	char	**tab;
	int		nbw;
	int		i;

	i = 0;
	nbw = 0;
	tab = NULL;
	while (s && *(s + i))
	{
		if (*(s + i) && is_spaced(*(s + i)) == 0)
			nbw++;
		while (*(s + i) && is_spaced(*(s + i)) == 0)
		{
			if (*(s + i) == '\'' || *(s + i) == '"')
				i = go_to_char_split(s, i);
			else
				i++;
		}
		while (*(s + i) && is_spaced(*(s + i)) == 1)
			i++;
	}
	tab = malloc(sizeof(char *) * (nbw + 1));
	if (tab == NULL)
		return (NULL);
	return (fill_tab(tab, s));
}
