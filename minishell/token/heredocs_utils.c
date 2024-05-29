/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:00:39 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/04 19:14:52 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (n == 0)
		return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
	while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0'
		&& *(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

void	add_length_of_var(char *line, int *i, int *length, t_core *core)
{
	char	*var_name;
	int		var_index_in_env;
	int		y;

	*i = *i + 1;
	var_name = get_var_name(line, *i, core);
	var_index_in_env = exist_in_env(var_name, core);
	y = ft_strlen(var_name);
	*i = *i + y - 1;
	if (var_index_in_env >= 0)
	{
		while (core->env && core->env[var_index_in_env][y])
		{
			y++;
			*length = *length + 1;
		}
	}
	free(var_name);
}

int	get_len_exit_status(int exit_status)
{
	int	len;

	if (exit_status == 0)
		return (1);
	len = 0;
	while (exit_status > 0)
	{
		exit_status /= 10;
		len++;
	}
	return (len);
}

void	add_length_of_exit_status(int *i, int *length, int exit_status)
{
	*i = *i + 1;
	*length = *length + get_len_exit_status(exit_status);
}

int	get_length_expanded_line(char *line, t_core *core)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& sep_dollar(line[i + 1],
				"+-\n\f\v\r\t %=$,.:;[]{}?\'\\\"/") == 0)
			add_length_of_var(line, &i, &length, core);
		else if (line[i] == '$' && line[i + 1] == '?')
			add_length_of_exit_status(&i, &length, core->exit_status);
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}
