/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:10:00 by mastie            #+#    #+#             */
/*   Updated: 2023/03/31 15:10:01 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_thread_status(struct s_thread_info *tinfo)
{
	struct timeval	tv;
	long int		timestamp;
	int				ret;

	ret = 1;
	pthread_mutex_lock(&tinfo->refs->able_to_print);
	pthread_mutex_lock(&tinfo->access_status);
	pthread_mutex_lock(&tinfo->refs->dead_p);
	timestamp = time_update(tinfo, &tv);
	if ((timestamp - tinfo->timeval) >= tinfo->refs->time_to_die
		&& tinfo->end == 0)
	{
		printf("%ld %d died\n", timestamp, tinfo->thread_num);
		tinfo->im_dead = 1;
		tinfo->refs->dead = 1;
		tinfo->refs->thread_print = 1;
	}
	else if (tinfo->end == 1)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&tinfo->refs->dead_p);
	pthread_mutex_unlock(&tinfo->access_status);
	pthread_mutex_unlock(&tinfo->refs->able_to_print);
	return (ret);
}
