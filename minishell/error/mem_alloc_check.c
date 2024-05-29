/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:36:37 by mastie            #+#    #+#             */
/*   Updated: 2023/09/20 18:02:07 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mem_list_chars(t_list **list, void *content, t_core *core)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = ft_lstnew(ft_strdup(content));
	if (tmp == NULL)
		ft_error_exit("Memory allocation failed", 1, core);
	ft_lstadd_back(list, tmp);
}

void	mem_list_wildcards(t_list **list, t_list *content, t_core *core)
{
	t_list	*tmp;

	tmp = ft_lstnew(new_t_wildcards(ft_lstsize(content)));
	if (tmp == NULL)
		ft_error_exit("Memory allocation failed", 1, core);
	ft_lstadd_back(list, tmp);
}
