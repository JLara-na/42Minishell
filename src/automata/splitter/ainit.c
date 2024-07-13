/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ainit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:39 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/14 00:25:48 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	splitter_alphabet_init(t_automata *a)
{
	a->alphabet = malloc(10 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" ");
	a->alphabet[1] = ft_strdup("|");
	a->alphabet[2] = ft_strdup("<");
	a->alphabet[3] = ft_strdup(">");
	a->alphabet[4] = ft_strdup("&");
	a->alphabet[5] = ft_strdup("\"");
	a->alphabet[6] = ft_strdup("\'");
	a->alphabet[7] = NULL;
}

void	splitter_errors_init(t_automata *a)
{
	a->errors = malloc(12 * (sizeof(char *)));
	a->errors[0] = ft_strdup("Empty string.");
	a->errors[1] = ft_strdup("Pipe Open");
	a->errors[2] = ft_strdup("Less Open");
	a->errors[3] = ft_strdup("Heredoc Open");
	a->errors[4] = ft_strdup("Great Open");
	a->errors[5] = ft_strdup("Append Open");
	a->errors[6] = ft_strdup("& Open");
	a->errors[7] = ft_strdup("\" Open");
	a->errors[8] = ft_strdup("\' Open");
	a->errors[9] = ft_strdup("Invalid Input");
	a->errors[10] = ft_strdup("Open keyword");
	a->errors[11] = NULL;
	a->errorlen = 10;
}

void	splitter_sactions_init(t_automata *a)
{
	(void)a;
}

void	splitter_tactions_init(t_automata *a)
{
	a->fta[SP_PIPE][SP_SPACEB] = get_token;
	a->fta[SP_PIPE][SP_WORDS] = get_token;
	a->fta[SP_PIPE][SP_DOUBLEQ] = get_token;
	a->fta[SP_PIPE][SP_SINGLEQ] = get_token;
	a->fta[SP_SPACEB][SP_PIPE] = get_token;
	a->fta[SP_SPACEW][SP_PIPE] = get_token;
	a->fta[SP_WORDS][SP_PIPE] = get_token;
}

void	splitter_automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	splitter_alphabet_init(a);
	splitter_errors_init(a);
	splitter_sactions_init(a);
	splitter_tactions_init(a);
	a->get_state = splitter_get_state;
}
