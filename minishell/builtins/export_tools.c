/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:46:18 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:19:05 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sequence_check_equal(char *str, char *check)
{
	int	i;
	int	j;

	i = -1;
	while (str && str[++i] && *(str + i) != '=')
	{
		j = -1;
		while (check[++j])
		{
			if (*(str + i) == check[j] && check[j] == '+'
				&& (*(str + i + 1) && *(str + i + 1) == '=') && i != 0)
				return (3);
			if (*(str + i) == check[j])
				return (1);
		}
	}
	return (0);
}

void	error_print(char *str)
{
	int		fd;

	fd = STDERR_FILENO;
	ft_putstr_fd("export : `", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

int	option_error(char *str)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd("export : `-", fd);
	if (*(str + 1))
	{
		ft_putchar_fd(*(str + 1), fd);
		ft_putstr_fd("': invalid option\n", fd);
	}
	else
		ft_putstr_fd("': export not a valid identifier\n", fd);
	return (-1);
}

int	valid_input_export(t_list *from)
{
	char	*str;

	str = (char *)from->content;
	if (ft_memchr(str, '=', ft_strlen(str)) != NULL
		&& (ft_isalpha(*str) == 1 || *str == '_'))
	{
		if (sequence_check_equal(str, "~@+-#*$.\\{}!") == 0)
			return (0);
		else if (sequence_check_equal(str, "~@+-#*$.\\{}!") == 3)
			return (3);
	}
	return (-1);
}

int	free_replace_check(char *str, int i, t_core *core)
{
	free(core->env[i]);
	core->env[i] = ft_strdup(str);
	if (core->env[i] == NULL)
		return (-1);
	return (0);
}
