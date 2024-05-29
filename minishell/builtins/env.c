/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:13:36 by mastie            #+#    #+#             */
/*   Updated: 2023/10/18 19:15:52 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_content *data, t_core *core)
{
	int	i;

	if (!data->arguments->next)
	{
		i = -1;
		while (core->env && core->env[++i])
			printf("%s\n", core->env[i]);
		return (0);
	}
	else
		printf("env : too many arguments\n");
	return (-1);
}

/*

	Verifier qu il n y ai aucune option

*/
