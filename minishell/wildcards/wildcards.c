/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:11:12 by mmalhada          #+#    #+#             */
/*   Updated: 2023/04/28 17::47 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lst(t_list *files_lst)
{
	char	*str;

	if (!files_lst)
	{
		printf("List is empty\n");
		return ;
	}
	printf("\nPrinting list :\n");
	while (files_lst)
	{
		str = files_lst->content;
		if (!str)
		{
			printf("Found null content\n");
			files_lst = files_lst->next;
			continue ;
		}
		if (str[0] == 0)
			printf("Found an empty string here\n");
		else
			printf("%s\n", str);
		files_lst = files_lst->next;
	}
	printf("\n");
}

t_list	*list_files_in_dir(DIR *directory, bool hidden_files, t_core *core)
{
	struct dirent	*file_infos;
	t_list			*files_lst;

	files_lst = NULL;
	errno = 0;
	file_infos = readdir(directory);
	while (file_infos)
	{
		if (file_infos->d_name[0] == '.')
		{
			if (hidden_files == true)
				ft_lstadd_back(&files_lst,
					ft_lstnew(ft_strdup(file_infos->d_name)));
		}
		else
		{
			if (hidden_files == false)
				ft_lstadd_back(&files_lst,
					ft_lstnew(ft_strdup(file_infos->d_name)));
		}
		file_infos = readdir(directory);
	}
	if (errno != 0)
		ft_perror_exit("Minishell ", errno, core);
	return (files_lst);
}

/*
wc_i = wilcard_index
*/
t_list	*get_files_with_wildcard(char *pattern,
	char *path_dir, t_list *wc_i, t_core *core)
{
	t_wldcard	wildcard_core;
	DIR			*directory;
	t_list		*files_matching_pattern;

	wildcard_core.pattern = pattern;
	wildcard_core.booleans.hidden_files = check_hidden_files(pattern);
	wildcard_core.booleans.star_at_the_end = check_star_at_the_end(pattern,
			wc_i);
	wildcard_core.booleans.star_at_the_start = check_star_at_the_start(pattern,
			wc_i);
	directory = opendir(path_dir);
	if (!directory)
		ft_perror_exit("Minishell ", errno, core);
	wildcard_core.files_lst = list_files_in_dir(directory,
			wildcard_core.booleans.hidden_files, core);
	files_matching_pattern = search_files_matching_pattern(wildcard_core, wc_i,
			core);
	if (closedir(directory))
		ft_perror_exit("Minishell ", errno, core);
	return (files_matching_pattern);
}
