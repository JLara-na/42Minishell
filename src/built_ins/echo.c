/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:31 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/23 17:12:19 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in_echo(t_token	*token)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (token->args[i] && ft_samestr(token->args[i], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (token->args[i])
	{
		ft_putstr_fd(token->args[i++], 1);
		if (token->args[i])
			ft_putstr_fd(" ", 1);
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
