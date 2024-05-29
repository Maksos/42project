/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:22:06 by mastie            #+#    #+#             */
/*   Updated: 2023/03/30 21:22:09 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleep_part(struct s_thread_info *tinfo, struct timeval *tv)
{
	long int	timestamp;
	int			ret;

	ret = 0;
	pthread_mutex_lock(&tinfo->refs->able_to_print);
	pthread_mutex_lock(&tinfo->access_status);
	timestamp = time_update(tinfo, tv);
	if (tinfo->refs->thread_print == 0)
		printf("%ld %d is sleeping\n", timestamp, tinfo->thread_num);
	else
		ret = 1;
	pthread_mutex_unlock(&tinfo->access_status);
	pthread_mutex_unlock(&tinfo->refs->able_to_print);
	if (ret == 0)
		usleep(tinfo->refs->time_to_sleep * 1000);
	return (ret);
}
