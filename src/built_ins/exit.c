/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:35 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/17 19:43:14 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipeless_entry(t_tree	*token_tree)
{
	t_token	*token;

	if (token_tree == NULL)
		return (0);
	token = (t_token *)token_tree->data;
	if (ft_samestr(token->line, "|"))
		return (1);
	return (pipeless_entry(token_tree->left)
		|| pipeless_entry(token_tree->right));
}

int	built_in_exit(t_shell	*shell)
{
	if (pipeless_entry(shell->token_tree))
	{
		free_env(shell);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
