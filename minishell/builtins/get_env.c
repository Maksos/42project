/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:24:11 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:28:02 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extracted_from_env(char *haystack, char *needle)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (*haystack && *needle && *haystack == *needle)
	{
		needle++;
		haystack++;
	}
	if (*needle == '\0' && *haystack)
	{
		while (*(haystack + i))
			i++;
		new = malloc(sizeof(char) * (i + 1));
		if (new == NULL)
			return (NULL);
		i = -1;
		while (*(haystack + (++i)))
			new[i] = *(haystack + i);
		new[i] = '\0';
	}
	return (new);
}

int	for_extraction(char *haystack, char *needle)
{
	while (*haystack && *needle && *haystack == *needle)
	{
		needle++;
		haystack++;
	}
	if (*needle == '\0' && *haystack)
		return (0);
	return (-1);
}

char	*get_env(char *str, t_core *core)
{
	int		i;
	char	*extracted;

	i = 0;
	extracted = NULL;
	while (core->env && core->env[i])
	{
		if (for_extraction(core->env[i], str) == 0)
		{
			extracted = extracted_from_env(core->env[i], str);
			if (extracted == NULL)
				return (NULL);
			return (extracted);
		}
		i++;
	}
	return (extracted);
}
