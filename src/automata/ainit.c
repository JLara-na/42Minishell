/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ainit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:39 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/28 00:37:57 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	alphabet_init(t_automata *a)
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

void	free_alph_err(t_automata *a)
{
	int	i;

	i = -1;
	while (a->alphabet[++i])
		free(a->alphabet[i]);
	free(a->alphabet);
	i = -1;
	while (a->errors[++i])
		free(a->errors[i]);
	free(a->errors);
}

void	errors_init(t_automata *a)
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

void	sactions_init(t_automata *a)
{
	(void)a;
	//a->fsa[PIPE] = pipe_found;
}

void	tactions_init(t_automata *a)
{
	(void)a;
}
