/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:18:49 by mastie            #+#    #+#             */
/*   Updated: 2021/12/18 11:56:14 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	not_charset(char c, char const *set)
{
	int		i;

	i = 0;
	while (set && set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*trim_and_fill(char *new, char const *s1, int start, int end)
{
	int		i;

	i = 0;
	while (s1 && s1[start] && start < end)
	{
		new[i] = s1[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		c;
	char	*new;

	i = 0;
	c = 0;
	new = NULL;
	while (s1 && s1[i] && not_charset(s1[i], set))
		i++;
	if (s1 && !s1[i])
		return (ft_strdup(""));
	if (s1)
		c = ft_strlen(s1);
	while (s1 && s1[c - 1] && not_charset(s1[c - 1], set))
		c--;
	new = malloc(sizeof(char) * (c - i + 1));
	if (new == NULL)
		return (NULL);
	return (trim_and_fill(new, s1, i, c));
}
