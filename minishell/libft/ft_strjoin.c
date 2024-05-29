/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:13:20 by mastie            #+#    #+#             */
/*   Updated: 2022/01/28 15:24:18 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_size(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (i == 0 && j == 0)
		return (0);
	return (i + j + 1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		o;
	char	*new;

	i = get_size(s1, s2);
	o = 0;
	new = NULL;
	new = malloc(sizeof(char) * i);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[o])
		new[i++] = s2[o++];
	new[i] = '\0';
	return (new);
}
