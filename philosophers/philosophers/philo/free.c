/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:57:28 by mastie            #+#    #+#             */
/*   Updated: 2023/01/15 18:57:29 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_threads(t_tables *table)
{
	if ((*table).philos_thread && (*table).philos_thread != NULL)
		free((*table).philos_thread);
}
