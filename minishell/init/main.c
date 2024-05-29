/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:40:50 by mastie            #+#    #+#             */
/*   Updated: 2023/10/25 00:53:36 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = 0;

void	ft_recreate_env(t_core *core)
{
	char	*str;
	char	*tmp;

	str = malloc(sizeof(char) * PATH_MAX);
	if (!str)
		exit(EXIT_FAILURE);
	str = getcwd(str, PATH_MAX);
	tmp = ft_strjoin("PWD=", str);
	free(str);
	core->env = malloc(sizeof(char *) * 3);
	core->env[0] = tmp;
	core->env[1] = ft_strdup("_=/usr/bin/");
	core->env[2] = NULL;
}

void	init_core(char **env, t_core *core)
{
	int	i;

	i = 0;
	init_globals(core);
	init_token_operator(core);
	if (env && !*env)
	{
		ft_recreate_env(core);
		return ;
	}
	while (env && env[i])
		i++;
	core->env = malloc(sizeof(char *) * (i + 1));
	if (core->env == NULL)
		ft_error_exit("Memory allocation failed\n", 1, core);
	i = -1;
	while (env && env[++i])
		core->env[i] = ft_strdup(env[i]);
	core->env[i] = NULL;
}

void	launcher(t_core *core)
{
	while (isatty(0))
	{
		core->input = readline("PROMPT> ");
		if (!core->input)
			ft_error_exit(NULL, 1, core);
		if (*core->input == '\0')
		{
			free(core->input);
			core->input = NULL;
		}
		else if (core->input)
		{
			add_history(core->input);
			input_control(core);
		}
	}
	if (core->env)
		free_chars(core->env);
}

int	main(int ac, char **av, char **env)
{
	t_core	core;

	if (ac && av && (isatty(0) && isatty(1) && isatty(2)))
	{
		signal_activation();
		init_core(env, &core);
		launcher(&core);
	}
	return (0);
}
