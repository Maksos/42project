/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:48:13 by mastie            #+#    #+#             */
/*   Updated: 2023/03/31 22:48:14 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	synchro_launch(struct s_thread_info *tinfo)
{
	pthread_mutex_lock(&(tinfo)->refs->simulation_start);
	pthread_mutex_unlock(&(tinfo)->refs->simulation_start);
	if (tinfo->thread_num % 2 == 0)
		usleep((tinfo->refs->time_to_eat) * 1000);
}

static void	*thread_start(void *arg)
{
	struct s_thread_info	*tinfo;
	struct timeval			tv;
	int						ret;

	tinfo = arg;
	ret = 0;
	synchro_launch(tinfo);
	while (ret == 0)
	{
		ret = lock_part(tinfo, &tv);
		if (ret == 0)
			ret = eat_part(tinfo, &tv);
		if (ret == 0)
			ret = sleep_part(tinfo, &tv);
		if (ret == 0)
			ret = think_part(tinfo, &tv);
		pthread_mutex_lock(&tinfo->refs->dead_p);
		if (tinfo->im_dead == 1 || tinfo->end == 1 || tinfo->refs->dead == 1)
		{
			pthread_mutex_unlock(&tinfo->refs->dead_p);
			return ((void *)0);
		}
		pthread_mutex_unlock(&tinfo->refs->dead_p);
	}
	return ((void *)-1);
}

/* PTHREAD_CREATE */
int	init_pthread_create(t_tables *table)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (pthread_mutex_init(&(*table).refs.able_to_print, NULL) == -1
		|| pthread_mutex_init(&(*table).refs.simulation_start, NULL) == -1
		|| pthread_mutex_init(&(*table).refs.dead_p, NULL) == -1)
		return (-1);
	pthread_mutex_lock(&(*table).refs.simulation_start);
	while (++i < (*table).refs.nb_philos && ret == 0)
		ret = pthread_create(&(*table).philos_thread[i].thread_id, NULL, \
			&thread_start, &(*table).philos_thread[i]);
	if (gettimeofday(&(*table).refs.tv, NULL) != 0)
		return (-1);
	pthread_mutex_unlock(&(*table).refs.simulation_start);
	return (0);
}
