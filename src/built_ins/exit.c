/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:35 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/11 21:18:36 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_value_check(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	built_in_exit(t_shell	*shell, t_token	*token)
{
	int	exit_status;

	exit_status = 0;
	if (ft_sarraysize(token->args) > 2)
		return (printf("exit: too many arguments\n"), EXIT_FAILURE);
	if (ft_sarraysize(token->args) == 2)
	{
		if (exit_value_check(token->args[1]))
			exit_status = (unsigned char)ft_atoi(token->args[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", token->args[1]);
			exit_status = 2;
		}
	}
	free_env(shell);
	if (!shell->child)
		printf(MSG_BYE);
	exit(exit_status);
	return (EXIT_FAILURE);
}
