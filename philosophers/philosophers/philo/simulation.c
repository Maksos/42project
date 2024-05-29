/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:13:32 by mastie            #+#    #+#             */
/*   Updated: 2023/03/11 16:13:33 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	destroy_mutex(t_tables *table, int i)
{
	int		ret;

	ret = pthread_mutex_destroy(&(*table).philos_thread[i].philo_fork);
	if (ret == 0)
		return (0);
	else if (ret == 16)
		printf("THREAD [%d] FAILED TO DESTROY MUTEX CAUSED BY EBUSY\n", \
			(*table).philos_thread[i].thread_num);
	else if (ret == 22)
		printf("THREAD [%d] FAILED TO DESTROY MUTEX CAUSED BY EINVAL\n", \
			(*table).philos_thread[i].thread_num);
	return (ret);
}

void	init_mutex_philo_part_2(t_tables *table)
{
	int	i;

	i = -1;
	while ((++i < (*table).refs.nb_philos))
	{
		if (i == (*table).refs.nb_philos - 1)
		{
			if (i == 0)
				(*table).philos_thread[i].right_fork = NULL;
			else
			{
				(*table).philos_thread[i].left_fork = \
					&(*table).philos_thread[0].philo_fork;
				(*table).philos_thread[i].right_fork = \
					&(*table).philos_thread[i].philo_fork;
			}
		}
		else
			(*table).philos_thread[i].right_fork = \
				&(*table).philos_thread[i + 1].philo_fork;
	}
}

int	init_mutex_philo(t_tables *table)
{
	int	i;

	i = -1;
	while ((++i < (*table).refs.nb_philos))
	{
		if (pthread_mutex_init \
			(&(*table).philos_thread[i].philo_fork, NULL) != 0
			|| pthread_mutex_init \
				(&(*table).philos_thread[i].access_status, NULL) != 0)
			return (-1);
		(*table).philos_thread[i].left_fork = \
			&(*table).philos_thread[i].philo_fork;
		(*table).philos_thread[i].refs = &(*table).refs;
	}
	init_mutex_philo_part_2(table);
	return (0);
}

static int	join_destroy(t_tables *table)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (++i < (*table).refs.nb_philos && ret == 0)
		ret = pthread_join((*table).philos_thread[i].thread_id, \
			&(*table).philos_thread[i].res);
	pthread_mutex_destroy(&(*table).refs.able_to_print);
	pthread_mutex_destroy(&(*table).refs.simulation_start);
	pthread_mutex_destroy(&(*table).refs.dead_p);
	i = -1;
	while (++i < (*table).refs.nb_philos)
		destroy_mutex(table, i);
	return (ret);
}

int	simulation(t_tables *table)
{
	int	ret;
	int	i;

	ret = init_mutex_philo(table);
	if (ret == 0)
		ret = init_pthread_create(table);
	if (ret != 0)
		return (-1);
	i = -1;
	while (++i < (*table).refs.nb_philos)
	{
		usleep(2000);
		if (check_thread_status(&(*table).philos_thread[i]) != 0)
			break ;
		if (i == (*table).refs.nb_philos - 1)
			i = -1;
	}
	return (join_destroy(table));
}
