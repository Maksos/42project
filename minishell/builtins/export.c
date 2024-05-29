/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:13:11 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:54:52 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_from_export(t_core *core, char *str)
{
	char	*data;
	char	*needle;
	char	*ret;

	data = NULL;
	ret = NULL;
	needle = extract_name_for_export(str);
	if (needle == NULL)
		return (NULL);
	data = get_env(needle, core);
	if (data == NULL)
	{
		free(needle);
		ret = crop_plus_in_str(str);
		return (ret);
	}
	ret = join_and_add(needle, data, rest_from_plus_export(str));
	free(needle);
	free(data);
	return (ret);
}

int	no_double_from_plus(char *str, char *env_str)
{
	int	i;

	i = 0;
	while ((*(str + i) && *(env_str + i))
		&& (*(str + i) == *(env_str + i)))
	{
		if (*(str + i) == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_new_var_in_env(t_core *core, int plus_add, t_list *from)
{
	t_list	*tmp;
	char	*new;
	char	*str;
	int		i;

	i = -1;
	tmp = NULL;
	str = (char *)from->content;
	if (plus_add == 1)
	{
		new = get_env_from_export(core, str);
		free(from->content);
		from->content = new;
		str = new;
	}
	while (core->env && core->env[++i])
	{
		if (no_double_from_plus(str, core->env[i]) == 0)
			mem_list_chars(&tmp, core->env[i], core);
	}
	mem_list_chars(&tmp, str, core);
	free_chars(core->env);
	core->env = t_list_to_strings(tmp);
	free_t_list(tmp, 1);
}

int	ft_export_on_check(t_content *data, t_core *core)
{
	int		i;
	t_list	*tmp;

	tmp = data->arguments->next;
	i = -1;
	while (tmp)
	{
		if (*(char *)tmp->content == '-')
			return (option_error((char *)tmp->content));
		i = exist_in_env((char *)tmp->content, core);
		if (i >= 0)
		{
			if (free_replace_check((char *)tmp->content, i, core) == -1)
				return (-1);
		}
		else if (valid_input_export(tmp) == 0)
			add_new_var_in_env(core, 0, tmp);
		else if (valid_input_export(tmp) == 3)
			add_new_var_in_env(core, 1, tmp);
		else
			error_print((char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_content *data, t_core *core)
{
	t_list	*tmp;

	tmp = data->arguments->next;
	if (!tmp)
		return (print_env_export(core));
	return (ft_export_on_check(data, core));
}
