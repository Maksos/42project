/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:23 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/17 04:42:24 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_pattern_between_stars(char *pat, int *i, t_list *wildcard_index,
		t_core *core)
{
	char	*pattern;
	int		y;

	y = 0;
	while (pat[*i] == '*' && is_star_interpreted(*i, wildcard_index) == true)
		*i = *i + 1;
	if (pat[*i] == 0)
		return (NULL);
	while (pat[*i] && (pat[*i] != '*' || is_star_interpreted(*i,
				wildcard_index) == false))
	{
		*i = *i + 1;
		y++;
	}
	pattern = malloc(sizeof(char) * (y + 1));
	if (!pattern)
		ft_perror_exit("Minishell ", errno, core);
	ft_strlcpy(pattern, &pat[*i - y], y + 1);
	return (pattern);
}

/*
wc_i == wildcard_index
*/
t_list	*create_list_of_patterns(char *pat, t_list *wc_i, t_core *core)
{
	char	*pattern;
	t_list	*patterns_lst;
	int		i;

	patterns_lst = NULL;
	i = 0;
	pattern = find_pattern_between_stars(pat, &i, wc_i, core);
	while (pattern)
	{
		ft_lstadd_back(&patterns_lst, ft_lstnew(pattern));
		pattern = find_pattern_between_stars(pat, &i, wc_i, core);
	}
	return (patterns_lst);
}

/*
wc_c = wildcard_core
wc_i = wildcard_index
*/
t_list	*search_files_matching_pattern(t_wldcard wc_c, t_list *wc_i,
	t_core *core)
{
	t_list	*patterns_lst;
	t_list	*files_matching;

	files_matching = NULL;
	patterns_lst = create_list_of_patterns(wc_c.pattern, wc_i, core);
	if (!patterns_lst)
		return (wc_c.files_lst);
	else
		files_matching = copy_files_matching(wc_c.files_lst,
				patterns_lst, wc_c.booleans);
	free_t_list(patterns_lst, 1);
	free_t_list(wc_c.files_lst, 0);
	return (files_matching);
}
