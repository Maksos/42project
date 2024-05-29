/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:16:22 by mastie            #+#    #+#             */
/*   Updated: 2022/03/07 19:11:34 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int	fd[3];
	char	*line[3];

	fd[0] = open("file1", O_RDONLY);
	fd[1] = open("file2", O_RDONLY);
	fd[2] = open("file3", O_RDONLY);
	printf("fd[0]=%d||fd[1]=%d||fd[2]==%d\n", fd[0], fd[1], fd[2]);
	while (1)
	{
		line[0] = get_next_line(fd[0]);
		line[1] = get_next_line(fd[1]);
		line[2] = get_next_line(fd[2]);
		if (line[0])
			printf("file1 =%s", line[0]);
		if (line[1])
			printf("file2 =%s", line[1]);
		if (line[2])
			printf("file3 =%s", line[2]);
		if (!line[0] && !line[1] && !line[2])
			break ;
		if (line[0])
			free(line[0]);
		if (line[1])
			free(line[1]);
		if (line[2])
			free(line[2]);
		line[0] = 0;
		line[1] = 0;
		line[2] = 0;
	}
	return (0);
}
