/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_token_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:16:50 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/22 03:56:13 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	split_in_token_lines(t_shell	*shell)
{
	int		a_state;
	char	*prompt;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	prompt = NULL;
	prompt = ft_strjoinfree(CUSTOM_208 M_SHELL_PROMPT CUSTOM_87 "~", pwd, 1);
	prompt = ft_strjoinfree(prompt, CUSTOM_208 "> " DEFAULT_SGR, 0);
	splitter_automata_init(&shell->splitter, shell);
	shell->splitter.str = readline(prompt);
	free(prompt);
	add_history(shell->splitter.str);
	a_state = evaluate(&shell->splitter);
	get_token(&shell->splitter, shell);
	if (a_state > shell->splitter.errorlen)
		return (free_alph_err(&shell->splitter), 1);
	else
	{
		printf(RED "%s\n" DEFAULT_SGR, shell->splitter.errors[a_state]);
		return (free_alph_err(&shell->splitter), 0);
	}
}
