/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ainit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:06:45 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/31 22:49:15 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	expander_alphabet_init(t_automata *a)
{
	a->alphabet = malloc(5 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" \t\n");
	a->alphabet[1] = ft_strdup("\"");
	a->alphabet[2] = ft_strdup("\'");
	a->alphabet[3] = ft_strdup("$");
	a->alphabet[4] = NULL;
}

void	expander_errors_init(t_automata *a)
{
	(void)a;
}

void	expander_sactions_init(t_automata *a)
{
	a->fsa[EX_LOOKING] = insert_chr;
	a->fsa[EX_DOUBLEQ] = insert_chr;
	a->fsa[EX_SINGLEQ] = insert_chr;
	a->fsa[EX_DOLLAR_OUT] = insert_var;
	a->fsa[EX_DOLLAR_IN] = insert_var;
}

void	expander_tactions_init(t_automata *a)
{
	(void)a;/*
	a->fta[EX_LOOKING][EX_LOOKING] = insert_chr;
	a->fta[EX_LOOKING][EX_DOUBLEQ] = insert_chr;
	a->fta[EX_LOOKING][EX_SINGLEQ] = insert_chr;
	a->fta[EX_DOUBLEQ][EX_DOUBLEQ] = insert_chr;
	a->fta[EX_SINGLEQ][EX_SINGLEQ] = insert_chr;
	a->fta[EX_DOUBLEQ][EX_LOOKING] = insert_chr;
	a->fta[EX_SINGLEQ][EX_LOOKING] = insert_chr;
	a->fta[EX_NAME_IN][EX_DOUBLEQ] = insert_chr;
	a->fta[EX_NAME_OUT][EX_LOOKING] = insert_chr;*/

}

void	expander_automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	expander_alphabet_init(a);
	expander_errors_init(a);
	expander_sactions_init(a);
	expander_tactions_init(a);
	a->get_state = expander_get_state;
}
