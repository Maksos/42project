/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_files_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:05:40 by mmalhada          #+#    #+#             */
/*   Updated: 2023/06/29 17:02:54 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	o;

	i = 0;
	if (needle && *needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		o = 0;
		if (haystack[i] == needle[o])
		{
			while (haystack[i] && haystack[i] == needle[o])
			{
				i++;
				o++;
			}
			if (needle[o] == '\0')
				return ((char *)haystack + i);
			i = i - o;
		}
		i++;
	}
	return (NULL);
}

char	*last_pattern(char *haystack, char *needle)
{
	size_t	i;
	size_t	o;

	i = 0;
	o = 0;
	if (needle && *needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		o = 0;
		if (haystack[i] == needle[o])
		{
			while (haystack[i] && haystack[i] == needle[o])
			{
				i++;
				o++;
			}
			if (needle[o] == 0 && haystack[i] == 0)
				return (haystack);
			i = i - o;
		}
		i++;
	}
	return (NULL);
}

char	*first_pattern(char *haystack, char *needle)
{
	size_t	i;
	size_t	o;

	i = 0;
	o = 0;
	if (needle && *needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && haystack[i] == needle[o])
	{
		i++;
		o++;
	}
	if (needle[o] == '\0')
		return (haystack + i);
	return (NULL);
}

int	is_file_matching_patterns(char *file_name, t_list *patterns_lst,
			t_booleans booleans)
{
	if (booleans.star_at_the_start == false)
	{
		file_name = first_pattern(file_name, (char *)patterns_lst->content);
		if (!file_name)
			return (false);
		patterns_lst = patterns_lst->next;
	}
	while (patterns_lst)
	{
		if (!patterns_lst->next && booleans.star_at_the_end == false)
		{
			file_name = last_pattern(file_name, (char *)patterns_lst->content);
			if (!file_name)
				return (false);
		}
		else
		{
			file_name = ft_strstr(file_name, (char *)patterns_lst->content);
			if (!file_name)
				return (false);
		}
		patterns_lst = patterns_lst->next;
	}
	return (true);
}

t_list	*copy_files_matching(t_list *files_lst, t_list *patterns_lst,
	t_booleans booleans)
{
	t_list	*files_matching;

	files_matching = NULL;
	while (files_lst)
	{
		if (is_file_matching_patterns((char *)files_lst->content, patterns_lst,
				booleans) == true)
			ft_lstadd_back(&files_matching, ft_lstnew(files_lst->content));
		else
			free(files_lst->content);
		files_lst = files_lst->next;
	}
	return (files_matching);
}
