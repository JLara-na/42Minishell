/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:44 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/10 18:25:51 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	tokenize_node(void	*token_ptr, void	*shell_ptr)
{
	t_shell	*shell;
	t_token	*token;

	shell = (t_shell *)shell_ptr;
	token = (t_token *)token_ptr;
	if (ft_samestr(token->line, "|"))
		return ;
	tokenizer_automata_init(&shell->tokenizer, token);
	shell->tokenizer.str = token->line;
	evaluate(&shell->tokenizer);
	free_alph_err(&shell->tokenizer);
}
