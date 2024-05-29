/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:47 by mastie            #+#    #+#             */
/*   Updated: 2023/01/12 14:55:49 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philos(t_tables *table, char *philos_verbose)
{
	int		i;

	i = 0;
	(*table).refs.nb_philos = ft_atoi(philos_verbose);
	if (((*table).refs.nb_philos == 0 && ft_strlen(philos_verbose) != 1)
		|| (*table).refs.nb_philos <= 0)
		return (-1);
	(*table).philos_thread = malloc(sizeof(t_thread_infos) * \
		(*table).refs.nb_philos);
	memset((*table).philos_thread, 0, sizeof(t_thread_infos) * \
		(*table).refs.nb_philos);
	if ((*table).philos_thread == NULL)
		return (-1);
	while (i < (*table).refs.nb_philos)
	{
		(*table).philos_thread[i].thread_num = i + 1;
		(*table).philos_thread[i].res = NULL;
		(*table).philos_thread[i].timeval = 0;
		(*table).philos_thread[i].im_dead = 0;
		(*table).philos_thread[i].must_eat = 0;
		(*table).philos_thread[i].end = 0;
		i++;
	}
	return (0);
}

int	init_5(t_tables *table, char **av)
{
	int	ret;

	ret = init_philos(table, av[1]);
	if (ret == 0)
		ret = input_control(table, av, 0);
	if (ret == 0)
		ret = simulation(table);
	return (ret);
}

int	init_6(t_tables *table, char **av)
{
	int	ret;

	ret = init_philos(table, av[1]);
	if (ret == 0)
		ret = input_control(table, av, 1);
	if (ret == 0)
		ret = simulation(table);
	return (ret);
}

int	main(int ac, char **av)
{
	t_tables	table;
	int			ret;

	table.philos_thread = NULL;
	table.refs.nb_philos = 0;
	table.refs.dead = -1;
	table.refs.thread_print = 0;
	ret = -1;
	if (ac == 6)
		ret = init_6(&table, av);
	else if (ac == 5)
		ret = init_5(&table, av);
	else
	{
		printf("Error\nUsage : number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [OPTIONNAL ARG: number\
			_of_times_each_philosopher_must_eat]\n");
	}
	ft_free_threads(&table);
	return (ret);
}
