/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:47:32 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/27 19:57:15 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	standard_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_data = SIGINT;
		if (write(1, "\n", 1) == -1)
			return (perror("error salto de linea"));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_handler(int signum)
{
	(void)signum;
	g_signal_data = SIGINT;
	signal(SIGINT, SIG_DFL);
	exit(0);
}

void	set_sig_handler(void (handler)(int signum), int sigquit_status)
{
	signal(SIGINT, handler);
	if (!sigquit_status)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_DFL);
}
