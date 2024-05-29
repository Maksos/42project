/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:54:42 by mastie            #+#    #+#             */
/*   Updated: 2023/03/30 20:54:44 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_left_fork(struct s_thread_info *tinfo, struct timeval *tv)
{
	int			ret;
	long int	timestamp;

	ret = pthread_mutex_lock(*(&tinfo->left_fork));
	if (ret != 0)
		return (ret);
	pthread_mutex_lock(&tinfo->refs->able_to_print);
	pthread_mutex_lock(&tinfo->access_status);
	pthread_mutex_lock(&tinfo->refs->dead_p);
	timestamp = time_update(tinfo, tv);
	if (tinfo->refs->thread_print == 0)
		printf("%ld %d has taken a fork\n", timestamp, tinfo->thread_num);
	else
	{
		pthread_mutex_unlock(*(&tinfo->left_fork));
		ret = 1;
	}
	pthread_mutex_unlock(&tinfo->refs->dead_p);
	pthread_mutex_unlock(&tinfo->access_status);
	pthread_mutex_unlock(&tinfo->refs->able_to_print);
	return (ret);
}

int	lock_right_fork_2(struct s_thread_info *tinfo, struct timeval *tv, int ret)
{
	long int	timestamp;

	pthread_mutex_lock(&tinfo->refs->able_to_print);
	pthread_mutex_lock(&tinfo->access_status);
	timestamp = time_update(tinfo, tv);
	if (tinfo->refs->thread_print == 0)
		printf("%ld %d has taken a fork\n", timestamp, tinfo->thread_num);
	else
	{
		pthread_mutex_unlock(*(&tinfo->right_fork));
		pthread_mutex_unlock(*(&tinfo->left_fork));
		ret = 1;
	}
	pthread_mutex_unlock(&tinfo->access_status);
	pthread_mutex_unlock(&tinfo->refs->able_to_print);
	return (ret);
}

int	lock_right_fork(struct s_thread_info *tinfo, struct timeval *tv)
{
	int			ret;

	if (*(&tinfo->right_fork) == NULL)
	{
		pthread_mutex_unlock(*(&tinfo->left_fork));
		return (1);
	}
	ret = pthread_mutex_lock(*(&tinfo->right_fork));
	if (ret != 0)
	{
		pthread_mutex_unlock(*(&tinfo->left_fork));
		return (ret);
	}
	return (lock_right_fork_2(tinfo, tv, ret));
}

int	lock_part(struct s_thread_info *tinfo, struct timeval *tv)
{
	int	ret;

	ret = lock_left_fork(tinfo, tv);
	if (ret == 0)
		ret = lock_right_fork(tinfo, tv);
	return (ret);
}
