/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:37 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/26 22:08:32 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



void	add_new_var(t_list	*enviroment, t_var	*newvar)
{
	t_list	*node;
	t_var	*var;

	node = NULL;
	var = NULL;
	node = ft_lstfind(enviroment, find_var, newvar->name);
	if (node)
	{
		var = (t_var *)(node->content);
		free(var->value);
		var->value = newvar->value;
		free(newvar->name);
		free(newvar);
		newvar = NULL;
	}
	else
		ft_lstadd_back(&enviroment, ft_lstnew(newvar));
}

void	built_in_export(t_shell *shell, t_token	*token)
{
	t_var	*newvar;
	int		i;
	int		j;

	newvar = NULL;
	i = 0;
	j = 0;
	if (!token->args[1])
		built_in_env(shell);
	while (token->args[++i])
	{
		j = ft_chrpos(token->args[i], '=');
		if (j != -1)
		{
			newvar = create_var(ft_substr(token->args[i], 0, j),
					ft_substr(token->args[i], j + 1, INT_MAX));
			add_new_var(shell->enviroment, newvar);
		}
	}
}
