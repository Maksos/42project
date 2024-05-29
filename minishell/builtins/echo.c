/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:14:24 by mastie            #+#    #+#             */
/*   Updated: 2023/10/27 19:18:14 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_space_print(t_list *current)
{
	t_list	*tmp;
	int		print;

	tmp = current->next;
	print = -1;
	while (tmp)
	{
		if ((char *)tmp->content)
			print = 1;
		tmp = tmp->next;
	}
	if (print == 1)
		printf(" ");
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (!*(str + i))
		return (0);
	if (*(str + i) == '-')
		i = 1;
	while (*(str + i) && *(str + i) == 'n')
		i++;
	if (!*(str + i))
		return (1);
	return (0);
}

int	ft_echo(t_content *data)
{
	t_list	*tmp;
	int		flag;

	if (!data)
		return (-1);
	tmp = data->arguments->next;
	flag = 0;
	while (tmp && check_n((char *)tmp->content) == 1)
	{
		flag = -1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if ((char *)tmp->content && *(char *)tmp->content)
			printf("%s", (char *)tmp->content);
		echo_space_print(tmp);
		tmp = tmp->next;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
