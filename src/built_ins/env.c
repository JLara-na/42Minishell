/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:33 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/09 21:23:07 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in_env(t_shell	*shell)
{
	int	i;

	i = -1;
	if (shell->local_env)
	{
		while (shell->local_env[++i])
			printf("%s\n", shell->local_env[i]);
		return (0);
	}
	return (1);
}
