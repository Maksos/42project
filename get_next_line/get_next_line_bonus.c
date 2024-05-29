/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:42:28 by mastie            #+#    #+#             */
/*   Updated: 2022/03/11 17:53:11 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

static int	size_to_nl(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char	*extracted_line(char *str)
{
	int		i;
	int		j;
	char	*line;

	line = NULL;
	i = size_to_nl(str);
	j = ft_strlen(str) - i;
	if (str && !str[i])
		free(str);
	if (j > 0)
		line = malloc(sizeof(char) * (j + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	if (str && str[i] && str[i] == '\n')
		i++;
	while (str && str[i])
		line[j++] = str[i++];
	line[j] = '\0';
	free(str);
	return (line);
}

static char	*extract_line(char *str)
{
	char	*ret;
	int		i;
	int		j;

	ret = NULL;
	i = size_to_nl(str);
	j = 0;
	if (i > 0 && !str[i])
		ret = malloc(sizeof(char) * (i + 1));
	else if (i > 0 || (i == 0 && str && str[i] && str[i] == '\n'))
		ret = malloc(sizeof(char) * (i + 2));
	if (ret == NULL)
		return (NULL);
	while (str && str[j] && j <= i)
	{
		ret[j] = str[j];
		ret[++j] = '\0';
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		buff[BUFFER_SIZE + 1];
	char		*retline;
	int			ret;

	ret = 0;
	while (fd >= 0 && fd <= 1024 && ret >= 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0 || (ret == 0 && line[fd] == NULL))
			return (NULL);
		buff[ret] = '\0';
		if (ret > 0 && line[fd] == NULL)
			line[fd] = ft_strdup_size(buff, ret);
		else if (ret > 0)
			line[fd] = ft_strcat_size(line[fd], buff, ret);
		if (ret == 0 || ft_strchr(buff, '\n') >= 0)
		{
			retline = extract_line(line[fd]);
			line[fd] = extracted_line(line[fd]);
			return (retline);
		}
	}
	return (NULL);
}
