/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:47:32 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/27 23:47:42 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *x)
{
	(void)x;
	(void)info;
	if (signum == SIGINT)
		printf("Has usado ctr C");
	if (signum == SIGQUIT)
		exit(EXIT_SUCCESS);
}

int	signals_init(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (1);
}
