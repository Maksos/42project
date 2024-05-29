/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:15:46 by mastie            #+#    #+#             */
/*   Updated: 2022/01/25 19:58:34 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	o;

	o = ft_strlen(dst);
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src && src[i] && (i + o) < (dstsize - 1))
	{
		dst[o + i] = src[i];
		i++;
		dst[o + i] = 0;
	}
	if (o < dstsize)
		return (o + ft_strlen(src));
	return (dstsize + ft_strlen(src));
}
