/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:17:23 by mmalhada          #+#    #+#             */
/*   Updated: 2023/06/23 18:17:00 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_star_interpreted(int index, t_list *wildcard_index)
{
	while (wildcard_index)
	{
		if (index == ((t_wildcards *)wildcard_index->content)->position)
			return (true);
		wildcard_index = wildcard_index->next;
	}
	return (false);
}

bool	check_hidden_files(char *pattern)
{
	if (pattern[0] == '.')
		return (true);
	else
		return (false);
}

bool	check_star_at_the_start(char *pattern, t_list *wildcard_index)
{
	int	i;

	i = 0;
	if (pattern[i] == '.')
		i++;
	if (pattern[i] == '*' && is_star_interpreted(i, wildcard_index) == true)
		return (true);
	else
		return (false);
}

bool	check_star_at_the_end(char *pattern, t_list *wildcard_index)
{
	int	i;

	i = 0;
	while (pattern[i])
		i++;
	if (pattern[i - 1] == '*' && is_star_interpreted(i - 1,
			wildcard_index) == true)
		return (true);
	else
		return (false);
}
