/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:55:57 by mastie            #+#    #+#             */
/*   Updated: 2023/09/20 18:34:02 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_cmp(char *haystack, char *needle)
{
	if (needle && haystack)
	{
		while (*haystack && *needle && *haystack == *needle)
		{
			haystack++;
			needle++;
			if (*needle && *needle == '=' && *haystack == '=')
				return (0);
			else if (!*needle && *haystack == '=')
				return (1);
		}
	}
	return (-1);
}

int	exist_in_env(char *str, t_core *core)
{
	int	i;

	i = -1;
	while (core->env && core->env[++i])
	{
		if (str_cmp(core->env[i], str) != -1)
			return (i);
	}
	return (-1);
}

char	**t_list_to_strings(t_list *tmp)
{
	char	**new;
	int		i;

	i = ft_lstsize(tmp);
	new = NULL;
	new = malloc(sizeof(char *) * (i + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (tmp)
	{
		new[i] = ft_strdup((char *)tmp->content);
		if (new[i] == NULL)
		{
			free_chars(new);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}
