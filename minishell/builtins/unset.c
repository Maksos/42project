/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:13:22 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:55:21 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

	add  not a valid identifier to unset :)

*/

void	adjust_env(int c, t_core *core)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = NULL;
	while (core->env && core->env[i])
	{
		if (i != c)
			mem_list_chars(&tmp, core->env[i], core);
		i++;
	}
	free_chars(core->env);
	core->env = t_list_to_strings(tmp);
	free_t_list(tmp, 1);
}

/*
Probably usless, in test file must be, in bash not indicate
*/
void	not_valid_identifier(char *str)
{
	ft_putstr_fd("unset `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/*
	if ((str && !*str))
		not_valid_identifier(str);

	put this if we need some check on identifiers
*/
int	ft_unset(t_content *data, t_core *core)
{
	t_list	*tmp;
	char	*str;
	int		i;

	tmp = data->arguments->next;
	i = -1;
	if (!tmp)
		return (0);
	while (tmp)
	{
		str = (char *)tmp->content;
		if (*str == '-')
		{
			ft_putstr_fd("unset: `-", STDERR_FILENO);
			if (*(str + 1))
				ft_putchar_fd(*(str + 1), STDERR_FILENO);
			ft_putstr_fd("': unset invalid option\n", STDERR_FILENO);
			return (-1);
		}
		i = exist_in_env(str, core);
		if (i >= 0 && ft_memchr(str, '=', ft_strlen(str)) == NULL)
			adjust_env(i, core);
		tmp = tmp->next;
	}
	return (0);
}
