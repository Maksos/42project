/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:58:26 by mastie            #+#    #+#             */
/*   Updated: 2023/01/12 14:58:27 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>
# include "ft_printf/ft_printf.h"
/* used on each thread to have acces to the rules of the table */
/* Number of philosopher arround the table */
/* Times philosophers must eat */
/* Time before philosopher straved */
/* Time for a philosopher to eat a lunch */
/* Time for a philosopher to sleep */
/* mutex lock by the last philo before sim and releas to begin sim */
/* mutex for print */
/* if != -1 -> First thread that died */
/* Print the status on threads */
/* For the First meal of each philosopher */
typedef struct s_ref
{
	int				nb_philos;
	int				must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	simulation_start;
	pthread_mutex_t	able_to_print;
	pthread_mutex_t	dead_p;
	int				dead;
	int				thread_print;
	struct timeval	tv;

}				t_refs;
/* Used as argument to thread_start() */
/* ID returned by pthread_create() also the nummber of the philosophe */
/* Mutex of the Philosopher fork */
/* Mutex of the Philosopher fork */
/* Mutex of the Philosopher fork */
/* Application-defined thread #NUMBER same value as thread_id */
/* Philosopher thread returned value */
/* Refs for the thread to accomplish the task */
/* LAST MEAL TIMEVAL*/
typedef struct s_thread_info
{
	pthread_t			thread_id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		philo_fork;
	int					thread_num;
	void				*res;
	struct s_ref		*refs;
	long int			timeval;
	pthread_mutex_t		access_status;
	int					must_eat;
	int					im_dead;
	int					end;

}				t_thread_infos;

/* Contain the refs and the philosophers */
typedef struct s_table
{
	struct s_ref			refs;
	struct s_thread_info	*philos_thread;

}				t_tables;
	/*FREE PARTS*/
void		ft_free_threads(t_tables *table);
/*INPUT CONTROL PARTS*/
int			input_control(t_tables *table, char **av, int opt);
/* SIMULATION PARTS*/
int			simulation(t_tables *table);
/* TIME PART*/
long int	time_update(struct s_thread_info *tinfo, struct timeval *tv);
/* LOCK_EAT_SLEEP_THINK */
int			lock_part(struct s_thread_info *tinfo, struct timeval *tv);
int			eat_part(struct s_thread_info *tinfo, struct timeval *tv);
int			sleep_part(struct s_thread_info *tinfo, struct timeval *tv);
int			think_part(struct s_thread_info *tinfo, struct timeval *tv);
/* STATUS CHECK PART*/
int			check_thread_status(struct s_thread_info *tinfo);
/* THREAD PARTS */
int			init_pthread_create(t_tables *table);

#endif
