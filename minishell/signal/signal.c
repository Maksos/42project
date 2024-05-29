/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:26:35 by mastie            #+#    #+#             */
/*   Updated: 2023/10/23 16:01:31 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int signum)
{
	if (signum == 2)
	{
		g_exit_status = 130;
		write(STDERR_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	signal_ignore(void)
{
	struct sigaction	sa_ign;

	sigemptyset(&sa_ign.sa_mask);
	sa_ign.sa_flags = 0;
	sa_ign.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_ign, NULL) == -1
		|| sigaction(SIGQUIT, &sa_ign, NULL) == -1)
		exit(EXIT_FAILURE);
}

void	signal_default(void)
{
	struct sigaction	sa_dfl;

	sigemptyset(&sa_dfl.sa_mask);
	sa_dfl.sa_flags = 0;
	sa_dfl.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa_dfl, NULL) == -1
		|| sigaction(SIGQUIT, &sa_dfl, NULL) == -1)
		exit(EXIT_FAILURE);
}

void	signal_activation(void)
{
	struct sigaction	act;

	rl_catch_signals = 0;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_handler = handler;
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) == -1
		|| sigaction(SIGQUIT, &act, NULL) == -1)
		exit(EXIT_FAILURE);
}
