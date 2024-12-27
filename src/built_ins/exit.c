/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:35 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/26 20:56:52 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	pipeless_entry(t_tree	*token_tree)
// {
// 	t_token	*token;

// 	token = (t_token *)token_tree->data;
// 	if (ft_samestr(token->line, "|"))
// 		return (0);
// 	return (pipeless_entry(token_tree->left)
// 		|| pipeless_entry(token_tree->right));
// }

int	built_in_exit(t_shell	*shell)
{
	free_env(shell);
	printf(MSG_BYE);
	exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
