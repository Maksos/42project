/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:14:09 by mastie            #+#    #+#             */
/*   Updated: 2023/03/11 16:14:10 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ici refaire un coup d opti de norme */

// int	check_atoi_ret(int ret, char *from)
// {
// 	int	i;

// 	i = 0;
// 	while ((from && from[i] == ' ') || (from[i] >= 9 && from[i] <= 13))
// 		i++;
// 	if (from && from[i] == '+')
// 		i++;
// 	if (ret == 0)
// 	{
// 		while (from && from[i])
// 		{
// 			if (from[i++] != '0')
// 				return (-1);
// 		}
// 	}
// 	while (from && from[i])
// 	{
// 		if (from[i] <= '0' || from[i] >= '9')
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

static int	control_time_to_die(t_tables *table, char *time_to_die)
{
	(*table).refs.time_to_die = ft_atoi(time_to_die);
	if (((*table).refs.time_to_die == 0 && ft_strlen(time_to_die) != 1))
		return (-1);
	if ((*table).refs.time_to_die <= 0)
		return (-1);
	return (0);
}

static int	control_time_to_eat(t_tables *table, char *time_to_eat)
{
	(*table).refs.time_to_eat = ft_atoi(time_to_eat);
	if (((*table).refs.time_to_eat == 0 && ft_strlen(time_to_eat) != 1))
		return (-1);
	if ((*table).refs.time_to_eat < 0)
		return (-1);
	return (0);
}

static int	control_time_to_sleep(t_tables *table, char *time_to_sleep)
{
	(*table).refs.time_to_sleep = ft_atoi(time_to_sleep);
	if (((*table).refs.time_to_sleep == 0 && ft_strlen(time_to_sleep) != 1))
		return (-1);
	if ((*table).refs.time_to_sleep < 0)
		return (-1);
	return (0);
}

static int	control_must_eat(t_tables *table, char *must_eat)
{
	(*table).refs.must_eat = ft_atoi(must_eat);
	if (((*table).refs.must_eat == 0 && ft_strlen(must_eat) != 1))
		return (-1);
	if ((*table).refs.must_eat < 0)
		return (-1);
	return (0);
}

int	input_control(t_tables *table, char **av, int opt)
{
	if (control_time_to_die(table, av[2]) == -1)
		return (-1);
	if (control_time_to_eat(table, av[3]) == -1)
		return (-1);
	if (control_time_to_sleep(table, av[4]) == -1)
		return (-1);
	if (opt == 0)
		(*table).refs.must_eat = -1;
	else if (opt == 1 && control_must_eat(table, av[5]) == -1)
		return (-1);
	return (0);
}
