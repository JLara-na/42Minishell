/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:13:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/26 20:24:06 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
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
*/

t_var	*create_var(char *name, char *value)
{
	t_var	*var;

	var = calloc(1, sizeof(t_var));
	var->name = name;
	var->value = value;
	return (var);
}

void	free_env(t_shell	*shell)
{
	t_list	*node;
	t_list	*aux;
	t_var	*var;

	node = shell->enviroment;
	while (node)
	{
		var = (t_var *)(node->content);
		free(var->name);
		free(var->value);
		free(var);
		aux = node->next;
		free(node);
		node = aux;
	}
}

void	import_env(t_shell	*shell, char **env)
{
	int	i;
	int	j;

	i = -1;
	shell->enviroment = NULL;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
		{
			if (env[i][j] == '=')
				ft_lstadd_back(&shell->enviroment, ft_lstnew(
						create_var(ft_substr(env[i], 0, j),
							ft_substr(env[i], j + 1, INT_MAX))));
		}
	}
}
