/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:31:07 by mmalhada          #+#    #+#             */
/*   Updated: 2023/11/04 19:32:10 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_env_var(char *var_name, char *expanded_line,
	int *y, t_core *core)
{
	int	var_index_in_env;
	int	i;
	int	len_var_name;

	len_var_name = ft_strlen(var_name);
	var_index_in_env = exist_in_env(var_name, core);
	if (var_index_in_env >= 0)
	{
		i = len_var_name;
		while (core->env && core->env[var_index_in_env][i])
		{
			expanded_line[*y] = core->env[var_index_in_env][i];
			i++;
			*y = *y + 1;
		}
	}
	free(var_name);
}

int	convert_base(char *base_symbols, char *expanded_line,
	long int number, int *y)
{
	if (number == 0)
		return (0);
	convert_base(base_symbols, expanded_line, number / 10, y);
	expanded_line[*y] = base_symbols[number % 10];
	*y = *y + 1;
	return (0);
}

void	replace_exit_status(char *expanded_line, int *y, int exit_status,
	int *i)
{
	long int	number;

	*i = *i + 2;
	if (exit_status == 0)
	{
		expanded_line[*y] = '0';
		*y = *y + 1;
		return ;
	}
	number = exit_status;
	if (number < 0)
	{
		expanded_line[*y] = '-';
		*y = *y + 1;
		number *= -1;
	}
	convert_base("0123456789", expanded_line, number, y);
}

void	create_expanded_line(char *line, char *expanded_line, t_core *core)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& sep_dollar(line[i + 1], "+-\n\f\v\r\t %=$,.:;[]{}?\'\\\"/") == 0)
		{
			i++;
			replace_env_var(get_var_name(line, i, core),
				expanded_line, &y, core);
			while (line[i]
				&& sep_dollar(line[i], "*+-\n\f\v\r\t %=$,.:;[]{}?\'\\\"/") == 0)
				i++;
		}
		else if (line[i] == '$' && line[i + 1] == '?')
			replace_exit_status(expanded_line, &y, core->exit_status, &i);
		else
			expanded_line[y++] = line[i++];
	}
	expanded_line[y] = 0;
}

char	*expand_var_in_heredoc(char *line, t_core *core)
{
	char	*expanded_line;

	if (replace(line) == 0)
		return (NULL);
	expanded_line = malloc(sizeof(char) * (get_length_expanded_line(line,
					core) + 1));
	if (!expanded_line)
		ft_perror_exit("Minishell ", errno, core);
	create_expanded_line(line, expanded_line, core);
	return (expanded_line);
}
