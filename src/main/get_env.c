/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:13:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/28 00:01:26 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(t_shell	*shell)
{
	int	i;

	i = 0;
	while (shell->local_env[i])
	{
		free(shell->local_env[i]);
		i++;
	}
	free(shell->local_env);
}

void	get_env(t_shell	*shell, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shell->local_env = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (env[i])
	{
		shell->local_env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->local_env[i] = NULL;
}
