/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ainit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:39 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/30 21:26:10 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	tokenizer_alphabet_init(t_automata *a)
{
	a->alphabet = malloc(6 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" ");
	a->alphabet[1] = ft_strdup("\"");
	a->alphabet[2] = ft_strdup("\'");
	a->alphabet[3] = ft_strdup("<");
	a->alphabet[4] = ft_strdup(">");
	a->alphabet[5] = NULL;
}

void	tokenizer_errors_init(t_automata *a)
{
	a->errors = malloc(5 * (sizeof(char *)));
	a->errors[0] = ft_strdup("Empty string.");
	a->errors[1] = ft_strdup("\" Open");
	a->errors[2] = ft_strdup("\' Open");
	a->errors[3] = ft_strdup("Invalid Input tk");
	a->errors[4] = NULL;
	a->errorlen = 4;
}

void	tokenizer_sactions_init(t_automata *a)
{
	(void)a;
}

void	tokenizer_tactions_init(t_automata *a)
{
	a->fta[TK_LESS][TK_SPACEB] = set_infile;
	a->fta[TK_LESS][TK_WORDS] = set_infile;
	a->fta[TK_LESS][TK_DOUBLEQ] = set_infile;
	a->fta[TK_LESS][TK_SINGLEQ] = set_infile;
	a->fta[TK_HEREDOC][TK_SPACEB] = set_infile;
	a->fta[TK_HEREDOC][TK_WORDS] = set_infile;
	a->fta[TK_HEREDOC][TK_DOUBLEQ] = set_infile;
	a->fta[TK_HEREDOC][TK_SINGLEQ] = set_infile;
	a->fta[TK_GREAT][TK_SPACEB] = set_outfile;
	a->fta[TK_GREAT][TK_WORDS] = set_outfile;
	a->fta[TK_GREAT][TK_DOUBLEQ] = set_outfile;
	a->fta[TK_GREAT][TK_SINGLEQ] = set_outfile;
	a->fta[TK_APPEND][TK_SPACEB] = set_outfile;
	a->fta[TK_APPEND][TK_WORDS] = set_outfile;
	a->fta[TK_APPEND][TK_DOUBLEQ] = set_outfile;
	a->fta[TK_EMPTY][TK_DOUBLEQ] = set_cmd_and_args;
	a->fta[TK_EMPTY][TK_SINGLEQ] = set_cmd_and_args;
	a->fta[TK_EMPTY][TK_WORDS] = set_cmd_and_args;
	a->fta[TK_SPACEW][TK_WORDS] = set_cmd_and_args;
	a->fta[TK_SPACEW][TK_DOUBLEQ] = set_cmd_and_args;
	a->fta[TK_SPACEW][TK_SINGLEQ] = set_cmd_and_args;
}

void	tokenizer_automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	tokenizer_alphabet_init(a);
	tokenizer_errors_init(a);
	tokenizer_sactions_init(a);
	tokenizer_tactions_init(a);
	a->get_state = tokenizer_get_state;
}
