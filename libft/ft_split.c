/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:45:47 by mastie            #+#    #+#             */
/*   Updated: 2022/01/25 20:41:46 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*extract_line(char const *s, int start, char c)
{
	char	*new;
	int		i;

	i = 0;
	while (s && s[start + i] && s[start + i] != c)
		i++;
	if (s[start + i] == c && i == 0)
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s && s[start + i] && s[start + i] != c)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	**fill_tab(char **tab, char const *s, char c)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[o++] = extract_line(s, i, c);
			if (tab[o - 1] == NULL)
				return (free_tab(tab));
		}
		while (s[i] && s[i] != c)
			i++;
	}
	tab[o] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nbw;
	int		i;

	i = 0;
	nbw = 0;
	tab = NULL;
	while (s && s[i])
	{
		if (s[i] && s[i] != c)
			nbw++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	tab = malloc(sizeof(char *) * (nbw + 1));
	if (tab == NULL)
		return (NULL);
	return (fill_tab(tab, s, c));
}
