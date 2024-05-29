/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_working.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:22:49 by mastie            #+#    #+#             */
/*   Updated: 2023/11/04 19:30:29 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_name_for_export(char *str)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	while (*(str + i) && *(str + i) != '+')
		i++;
	new = malloc(sizeof(char) * (i + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (*(str + i) && *(str + i) != '+')
	{
		new[i] = *(str + i);
		i++;
	}
	new[i++] = '=';
	new[i] = '\0';
	return (new);
}

char	*crop_plus_in_str(char *str)
{
	char	*new;
	int		i;
	int		ii;

	i = -1;
	ii = -1;
	new = malloc(sizeof(char) * ft_strlen(str));
	while (*(str + ++i))
	{
		*(new + ++ii) = *(str + i);
		if (*(str + i) == '+' && *(str + i + 1) == '=')
		{
			i++;
			break ;
		}
	}
	while (*(str + i))
	{
		*(new + ii) = *(str + i);
		i++;
		ii++;
	}
	*(new + ii) = '\0';
	return (new);
}

char	*join_and_add(char *p1, char *p2, char *p3)
{
	char	*new;
	char	*new_ret;

	new = NULL;
	new_ret = NULL;
	new = ft_strjoin(p1, p2);
	if (p3)
	{
		new_ret = ft_strjoin(new, p3);
		free(p3);
		free(new);
		return (new_ret);
	}
	return (new);
}

char	*rest_from_plus_export(char *str)
{
	char	*new;
	int		i;
	int		ii;

	new = NULL;
	i = 0;
	ii = 0;
	while (*(str + i) && *(str + i) != '=')
		i++;
	i++;
	if (*(str + i))
		new = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	else
		new = malloc(sizeof(char) * 1);
	while (*(str + i))
	{
		new[ii] = *(str + i);
		ii++;
		i++;
	}
	new[ii] = '\0';
	return (new);
}

int	print_env_export(t_core *core)
{
	int		i;

	i = 0;
	while (core->env && core->env[i])
	{
		printf("%s\n", core->env[i]);
		i++;
	}
	return (0);
}
