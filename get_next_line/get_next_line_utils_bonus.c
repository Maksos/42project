/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:42:50 by mastie            #+#    #+#             */
/*   Updated: 2022/02/05 14:43:16 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup_size(char *str, int s)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	if (s > 0)
		ret = malloc(sizeof(char) * (s + 1));
	if (ret == NULL)
		return (NULL);
	while (str && str[i])
	{
		ret[i] = str[i];
		ret[++i] = '\0';
	}
	return (ret);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	if (str && str[i] && str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strcat_size(char *s1, char *s2, int ss2)
{
	char		*ret;
	int			i;
	int			j;

	ret = NULL;
	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ss2 + 1));
	if (ret == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		ret[i + j] = s2[j];
		ret[i + ++j] = '\0';
	}
	free(s1);
	return (ret);
}
