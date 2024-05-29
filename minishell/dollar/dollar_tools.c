/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:22:49 by mastie            #+#    #+#             */
/*   Updated: 2023/11/04 19:40:24 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sep_dollar(char c, char *ref)
{
	int	i;

	i = 0;
	while (*(ref + i))
	{
		if (*(ref + i) == c)
			return (1);
		i++;
	}
	return (0);
}

int	dollar_name_length(char *str, int i)
{
	int	size;

	size = 0;
	i++;
	while (*(str + i + size)
		&& sep_dollar(str[i + size], "*+-\n\f\v\r\t %=$,.:;[]{}?\'\\\"/") == 0)
	{
		size++;
	}
	return (size);
}

char	*extract_name(char *str, int start, int lenght)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	new = malloc(sizeof(char) * (lenght + 1));
	if (new == NULL)
		return (NULL);
	while (*(str + start + i) && i < lenght)
	{
		new[i] = *(str + start + i);
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	adjust_tmp(int i, char *str, t_list **tmp_str, t_core *core)
{
	int	save;

	save = i;
	while (*(str + i))
	{
		if (*(str + i) == '=' && i == save)
			i++;
		else
			mem_list_chars(tmp_str, &*(str + (i++)), core);
	}
}

char	*get_var_name(char *line, int length, t_core *core)
{
	int		i;
	ssize_t	length_var_name;
	char	*var_name;

	i = length;
	while (line[i]
		&& sep_dollar(line[i], "*+-\n\f\v\r\t %=$,.:;[]{}?\'\\\"/") == 0)
		i++;
	length_var_name = i - length + 2;
	var_name = malloc(sizeof(char) * length_var_name);
	if (!var_name)
		ft_perror_exit("Minishell", 13, core);
	ft_strlcpy(var_name, line + length, length_var_name);
	var_name[length_var_name - 2] = '=';
	var_name[length_var_name - 1] = 0;
	return (var_name);
}
