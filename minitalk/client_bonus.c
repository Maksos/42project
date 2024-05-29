/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:11:37 by mastie            #+#    #+#             */
/*   Updated: 2022/10/22 19:15:49 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*
	ulimit -s  is needed for huge input 16777216 || 8388608
*/

static t_client_data	g_client;

static void	errors(char *str)
{
	int	i;

	i = 0;
	if (g_client.size && g_client.size != NULL)
		free(g_client.size);
	ft_printf("\033[0;31m");
	while (str && str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	ft_printf("\033[0m");
	exit(EXIT_FAILURE);
}

static void	transiting_data(void)
{
	if (g_client.size != NULL)
	{
		if ((g_client.size[g_client.i] & (1 << g_client.bit++)) != 0)
		{
			if (kill(g_client.server_pid, SIGUSR1) == -1)
				errors("Erreur lors de la transmition d un bit\n");
		}
		else if (kill(g_client.server_pid, SIGUSR2) == -1)
			errors("Erreur lors de la transmition d un bit\n");
		if (pause() != -1)
			errors("Erreur PAUSE FAILED\n");
	}
	else
	{
		if ((g_client.str[g_client.i] & (1 << g_client.bit++)) != 0)
		{
			if (kill(g_client.server_pid, SIGUSR1) == -1)
				errors("Erreur lors de la  transition d'un bit au serveur.\n");
		}
		else if (kill(g_client.server_pid, SIGUSR2) == -1)
			errors("Erreur lors de la  transition d'un bit au serveur.\n");
		if (pause() != -1)
			errors("Erreur PAUSE FAILED\n");
	}
}

static void	handling_size(void)
{
	if (!g_client.size[g_client.i])
	{
		g_client.i = 0;
		free(g_client.size);
		g_client.size = NULL;
	}
	else if (g_client.size[g_client.i])
		g_client.i++;
	transiting_data();
}

static void	handler(int signo, siginfo_t *siginfo, void *ucontext)
{
	(void)ucontext;
	if (signo == SIGUSR1)
		transiting_data();
	else if (signo == SIGUSR2)
	{
		g_client.bit = 0;
		if (g_client.size != NULL)
			handling_size();
		else
		{
			if (!g_client.str[g_client.i])
			{
				ft_printf("\033[0;33mSERVEUR [\033[0;35m%d", siginfo->si_pid);
				ft_printf("\033[0;33m]\033[0;32m CONFIRMATION DU PID \033[0;33m[");
				ft_printf("\033[0;35m%d\033[0;33m]\n\033[0m", getpid());
				exit(EXIT_SUCCESS);
			}
			else if (g_client.str[g_client.i])
			{
				g_client.i++;
				transiting_data();
			}
		}
	}
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	if (ac == 3)
	{
		act.sa_sigaction = &handler;
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
		if (sigaction(SIGUSR1, &act, NULL) == -1
			|| sigaction(SIGUSR2, &act, NULL) == -1
			|| sigaction(SIGSEGV, &act, NULL) == -1)
			errors("Sigaction a echouer\n");
		g_client.server_pid = ft_atoi(av[1]);
		if (g_client.server_pid <= 0 || input_pid(av[1]) == -1)
			errors("Le PID n est pas valide!\n");
		g_client.str = av[2];
		g_client.size = ft_itoa(ft_strlen(av[2]));
		if (kill(g_client.server_pid, SIGUSR1) == -1)
			errors("Erreur pas de communication avec ce PID.\n");
		else if (pause() != -1)
			errors("Erreur PAUSE FAILED.\n");
	}
	else
		errors("Erreur\nUsage: ./client SERVER_PID ARG\n");
	return (0);
}
