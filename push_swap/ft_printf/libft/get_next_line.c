/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:48:53 by mastie            #+#    #+#             */
/*   Updated: 2022/10/29 22:58:36 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
	else if (i > 0)
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

// send the addr of line to keep the rest of readed chars

char	*get_next_line(int fd)
{
	static char	*line;
	char		buff[BUFFER_SIZE + 1];
	char		*retline;
	int			ret;

	ret = 0;
	while (fd >= 0 && fd <= 1024 && ret >= 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0 || (ret == 0 && line == NULL))
			return (NULL);
		buff[ret] = '\0';
		if (ret > 0 && line == NULL)
			line = ft_strdup_size(buff, ret);
		else if (ret > 0)
			line = ft_strcat_size(line, buff, ret);
		if (ret == 0 || ft_strchr_gnl(buff, '\n') >= 0)
		{
			retline = extract_line(line);
			line = extracted_line(line);
			return (retline);
		}
	}
	return (NULL);
}
