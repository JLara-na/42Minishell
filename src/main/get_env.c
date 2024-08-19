/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:13:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/09 21:24:14 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_path_var(t_shell	*shell)
{
	int	i;

	i = -1;
	while (shell->local_env[++i])
	{
		if (!ft_memcmp(shell->local_env[i], "PATH=", 4))
			shell->path_var = ft_split(shell->local_env[i]
					+ ft_strlen("PATH="), ':');
	}
}

void	free_env(t_shell	*shell)
{
	int	i;

	i = -1;
	if (shell->local_env)
	{
		while (shell->local_env[++i])
			free(shell->local_env[i]);
		free(shell->local_env);
	}
	i = -1;
	if (shell->path_var)
	{
		while (shell->path_var[++i])
			free(shell->path_var[i]);
		free(shell->path_var);
	}
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
	get_path_var(shell);
}
