/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:47:30 by mastie            #+#    #+#             */
/*   Updated: 2023/03/28 12:47:31 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	time_update(struct s_thread_info *tinfo, struct timeval *tv)
{
	long int	ret;

	if (gettimeofday(tv, NULL) != 0)
		return (-1);
	ret = ((*tv).tv_sec * (u_int64_t)1000) + ((*tv).tv_usec / 1000);
	ret -= (tinfo->refs->tv.tv_sec * (u_int64_t)1000) \
		+ (tinfo->refs->tv.tv_usec / 1000);
	return (ret);
}
