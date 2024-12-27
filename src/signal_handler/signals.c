/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:47:32 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/27 13:47:46 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	signal_handler(int signum, siginfo_t *info, void *x)
// {
// 	(void)info;
// 	(void)x;
// 	if (signum == SIGINT)
// 	{
// 		if (write(1, "\n", 1) == -1)
// 			return ;
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	return ;
// }

// int	signals_init(t_shell	*shell)
// {
// 	struct sigaction	sa;

// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = signal_handler;
// 	sigaction(SIGINT, &sa, (void *)shell);
// 	sigaction(SIGQUIT, &sa, (void *)shell);
// 	return (1);
// }

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
}

void	set_sig_handler(void (handler)(int signum), int	sigquit_status)
{
	signal(SIGINT, handler);
	if (!sigquit_status)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_DFL);
}
