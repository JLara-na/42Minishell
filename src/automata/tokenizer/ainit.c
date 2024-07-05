/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ainit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:39 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/05 21:38:43 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	tokenizer_alphabet_init(t_automata *a)
{
	a->alphabet = malloc(5 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" ");
	a->alphabet[1] = ft_strdup("|");
	a->alphabet[2] = ft_strdup("\"");
	a->alphabet[3] = ft_strdup("\'");
	a->alphabet[4] = NULL;
}

void	tokenizer_errors_init(t_automata *a)
{
	a->errors = malloc(6 * (sizeof(char *)));
	a->errors[0] = ft_strdup("Empty string.");
	a->errors[1] = ft_strdup("\" Open");
	a->errors[2] = ft_strdup("\' Open");
	a->errors[3] = ft_strdup("Pipe Open");
	a->errors[4] = ft_strdup("Invalid Input");
	a->errors[5] = NULL;
	a->errorlen = 5;
}

void	tokenizer_sactions_init(t_automata *a)
{
	(void)a;
}

void	tokenizer_tactions_init(t_automata *a)
{
	(void)a;
	a->fta[TK_PIPE][TK_SPACEB] = get_token;
	a->fta[TK_PIPE][TK_WORDS] = get_token;
	a->fta[TK_PIPE][TK_DOUBLEQ] = get_token;
	a->fta[TK_PIPE][TK_SINGLEQ] = get_token;
	a->fta[TK_SPACEB][TK_PIPE] = get_token;
	a->fta[TK_SPACEW][TK_PIPE] = get_token;
	a->fta[TK_WORDS][TK_PIPE] = get_token;
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
