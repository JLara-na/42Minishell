/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:42 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/22 03:51:39 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_node_var(t_list	*node)
{
	t_var	*aux_var;

	aux_var = NULL;
	aux_var = (t_var *)(node->content);
	free(aux_var->name);
	free(aux_var->value);
	free(aux_var);
	free(node);
}

void	delete_env_node(t_list	**env, t_list	*node_to_delete)
{
	t_list	*current;
	t_list	*aux_list;

	if (env == NULL || *env == NULL || node_to_delete == NULL)
		return ;
	if (*env == node_to_delete)
	{
		aux_list = *env;
		*env = (*env)->next;
		free_node_var(aux_list);
		return ;
	}
	current = *env;
	while (current != NULL && current->next != node_to_delete)
		current = current->next;
	if (current != NULL && current->next == node_to_delete)
	{
		aux_list = current->next;
		current->next = current->next->next;
		free_node_var(aux_list);
	}
}

int	built_in_unset(t_shell	*shell, t_token *token)
{
	t_list	*node;
	int		exit_status;
	int		i;

	node = NULL;
	exit_status = 0;
	i = 0;
	while (token->args[++i])
	{
		node = ft_lstfind(shell->enviroment, find_var, token->args[i]);
		if (node)
			delete_env_node(&shell->enviroment, node);
		else
			exit_status = 1;
	}
	return (exit_status);
}
