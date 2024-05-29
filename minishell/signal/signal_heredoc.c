/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalhada <mmalhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:53:28 by mmalhada          #+#    #+#             */
/*   Updated: 2023/10/27 16:53:29 by mmalhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_heredoc(int signum)
{
	if (signum == 2)
	{
		g_exit_status = 130;
		write(STDERR_FILENO, " ^C", 3);
		close (STDIN_FILENO);
	}
}

void	signal_activation_heredoc(void)
{
	struct sigaction	act;

	rl_catch_signals = 0;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_handler = handler_heredoc;
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) == -1
		|| sigaction(SIGQUIT, &act, NULL) == -1)
		exit(EXIT_FAILURE);
}
