/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:12:11 by mastie            #+#    #+#             */
/*   Updated: 2022/10/23 16:31:54 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_server_data		g_clients[4194304];

static void	kill_error(int num)
{
	ft_printf("\033[0;31m");
	if (num == 1)
		write(2, "Cant confirm the received byte\n", 31);
	else if (num == 2)
		write(2, "Cant confirm the EOL\n", 21);
	else if (num == 3)
		write(2, "Error PAUSE failed\n", 18);
	else if (num == 4)
		write(1, "Error server!\nUsage: ./server\n", 30);
	else if (num == 5)
		write(1, "Error SIGACTION failed\n", 23);
	else if (num == 6)
		write(1, "Error MALLOC FAILED\n", 20);
	ft_printf("\033[0m");
	exit(EXIT_FAILURE);
}

static void	fill_recieved_size(int pid)
{
	static int	mult;

	if (g_clients[pid].c != '\0')
	{
		if (mult == 0)
			mult = 1;
		else
			mult = 10;
		g_clients[pid].size *= mult;
		g_clients[pid].size += (g_clients[pid].c - '0');
		g_clients[pid].c = 0;
	}
	else if (g_clients[pid].c == '\0')
	{
		g_clients[pid].sized = 1;
		mult = 0;
		if (g_clients[pid].size > 0)
		{
			g_clients[pid].str = malloc(sizeof(char) * ++g_clients[pid].size);
			if (g_clients[pid].str == NULL)
				kill_error(6);
		}
	}
}

static void	fill_recieved_byte(siginfo_t *siginfo)
{
	int			pid;

	pid = siginfo->si_pid;
	g_clients[pid].bit = 0;
	if (g_clients[pid].sized == 0)
		fill_recieved_size(pid);
	else
	{
		if (g_clients[pid].c != '\0')
		{
			g_clients[pid].str[g_clients[pid].i++] = g_clients[pid].c;
			g_clients[pid].c = 0;
		}
		else if (g_clients[pid].c == '\0')
		{
			if (g_clients[pid].str && g_clients[pid].i > 0)
				g_clients[pid].str[g_clients[pid].i] = '\0';
			ft_printf("\033[0;33mSERV:[\033[0;35m%d\033[0;33m]", getpid());
			ft_printf(" END RECEPTION FROM PID [\033[0;35m%d\033[0;33m]\n", pid);
			ft_printf("SERV:[\033[0;36m%s\033[0;33m]\n\033[0m", g_clients[pid].str);
			if (g_clients[pid].str && g_clients[pid].str != NULL)
				free(g_clients[pid].str);
			g_clients[pid].str = NULL;
		}
	}
}

static void	handler(int signo, siginfo_t *siginfo, void *ucontext)
{
	(void)ucontext;
	if (g_clients[siginfo->si_pid].init == 0)
	{
		g_clients[siginfo->si_pid].init = 1;
		if (kill(siginfo->si_pid, SIGUSR1) == -1)
			kill_error(1);
	}
	else
	{
		if (signo == SIGUSR1)
			g_clients[siginfo->si_pid].c
				|= (1 << g_clients[siginfo->si_pid].bit);
		g_clients[siginfo->si_pid].bit++;
		if (g_clients[siginfo->si_pid].bit < 8)
		{
			if (kill(siginfo->si_pid, SIGUSR1) == -1)
				kill_error(1);
		}
		else
		{
			fill_recieved_byte(siginfo);
			if (kill(siginfo->si_pid, SIGUSR2) == -1)
				kill_error(2);
		}
	}
}

int	main(int ac, char **av)
{
	struct sigaction	act;
	struct sigaction	oldact;
	sigset_t			sigset;

	(void)av;
	if (ac != 1)
		kill_error(4);
	act.sa_sigaction = &handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO | SA_ONSTACK | SA_NODEFER;
	ft_printf("\033[0;33mSERVER PID = [\033[0;35m%d\033[0;33m]\n\033[0m", getpid());
	if (sigaction(SIGUSR1, &act, &oldact) == -1
		|| sigaction(SIGUSR2, &act, &oldact) == -1
		|| sigaction(SIGSEGV, &act, &oldact) == -1
		|| sigaction(SIGSEGV, &oldact, NULL) == -1)
		kill_error(5);
	while (1)
	{
		sigemptyset(&sigset);
		sigaddset(&sigset, SIGUSR1);
		sigaddset(&sigset, SIGUSR2);
		if (pause() != -1)
			kill_error(3);
	}
	return (0);
}
