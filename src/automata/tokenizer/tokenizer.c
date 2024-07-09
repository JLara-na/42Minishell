/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:15:44 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/09 23:35:17 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	tokenizer(t_shell *shell)
{
	int	a_state;

	tokenizer_automata_init(&shell->tokenizer, shell);
	shell->tokenizer.str = shell->splitter.str;
	a_state = evaluate(&shell->tokenizer);
	printf(BLUE "%d\n" DEF_COLOR, a_state);
	free_alph_err(&shell->tokenizer);
}