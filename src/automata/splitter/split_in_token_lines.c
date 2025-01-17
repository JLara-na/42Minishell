/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_token_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:16:50 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/17 17:45:26 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	split_in_token_lines(t_shell	*shell)
{
	int		a_state;
	char	*prompt;

	prompt = NULL;
	prompt = generate_prompt(shell);
	splitter_automata_init(&shell->splitter, shell);
	shell->splitter.str = readline(prompt);
	free(prompt);
	if (shell->splitter.str == NULL)
	{
		printf(MSG_BYE);
		exit(EXIT_SUCCESS);
	}
	add_history(shell->splitter.str);
	a_state = evaluate(&shell->splitter);
	get_token(&shell->splitter, shell);
	if (a_state > shell->splitter.errorlen)
		return (free_alph_err(&shell->splitter), 1);
	else
	{
		printf(RED "%s\n" DEFAULT_SGR, shell->splitter.errors[a_state]);
		shell->exit_status = 127;
		return (free_alph_err(&shell->splitter), 0);
	}
}
