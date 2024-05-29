/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:46:29 by mastie            #+#    #+#             */
/*   Updated: 2021/12/07 18:21:42 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	void	*t;

	i = 0;
	t = b;
	while (i < len)
	{
		*(unsigned char *)b = (unsigned char)c;
		b++;
		i++;
	}
	return (t);
}
