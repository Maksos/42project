/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:31:40 by mastie            #+#    #+#             */
/*   Updated: 2022/01/25 20:59:12 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0' && s[0] == '\0')
		return ((char *)s + 0);
	while (s && s[i])
	{
		if ((char)c == s[i])
			return ((char *)s + i);
		else if ((char)c == s[i + 1])
			return ((char *)s + i + 1);
		i++;
	}
	return (NULL);
}
