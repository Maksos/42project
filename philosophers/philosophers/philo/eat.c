/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:06:31 by mastie            #+#    #+#             */
/*   Updated: 2023/03/30 21:06:32 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock(struct s_thread_info *tinfo)
{
	if (pthread_mutex_unlock(*(&tinfo->left_fork)) != 0)
		printf("TRHEAD [%d] MUTEX UNLOCK FAILED\n", tinfo->thread_num);
	if (pthread_mutex_unlock(*(&tinfo->right_fork)) != 0)
		printf("THREAD [%d] MUTEX UNLOCK FAILED\n", tinfo->thread_num);
}

int	eat_part(struct s_thread_info *tinfo, struct timeval *tv)
{
	long int	timestamp;
	int			ret;

	ret = 0;
	pthread_mutex_lock(&tinfo->refs->able_to_print);
	pthread_mutex_lock(&tinfo->access_status);
	pthread_mutex_lock(&tinfo->refs->dead_p);
	timestamp = time_update(tinfo, tv);
	if (tinfo->refs->thread_print == 0)
		printf("%ld %d is eating\n", timestamp, tinfo->thread_num);
	else
		ret = 1;
	tinfo->timeval = timestamp;
	tinfo->must_eat++;
	if (tinfo->refs->must_eat == tinfo->must_eat)
		tinfo->end = 1;
	pthread_mutex_unlock(&tinfo->refs->dead_p);
	pthread_mutex_unlock(&tinfo->access_status);
	pthread_mutex_unlock(&tinfo->refs->able_to_print);
	if (ret == 0)
		usleep(tinfo->refs->time_to_eat * 1000);
	unlock(tinfo);
	return (ret);
}
