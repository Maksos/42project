/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:40:34 by mastie            #+#    #+#             */
/*   Updated: 2021/12/07 18:14:23 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	o;

	i = 0;
	if (needle && *needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		o = 0;
		if (haystack[i] == needle[o])
		{
			while (haystack[i] && i < len && haystack[i] == needle[o])
			{
				i++;
				o++;
			}
			if (needle[o] == '\0')
				return ((char *)haystack + (i - o));
			i = i - o;
		}
		i++;
	}
	return (NULL);
}
