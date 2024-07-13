/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:45:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/13 22:40:33 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	0	1	2	3	4	5	6	7	Column characters
//	\s	|	<	>	&	"	'	^

int	splitter_get_state(int i, int j)
{
	const int	states[][8] = {
	{0, 9, 2, 9, 9, 7, 8, 12},	// 0  Empty
	{10, 9, 9, 9, 9, 7, 8, 12},	// 1  Pipe Open (NO CONTEMPLAMOS OR)
	{10, 9, 3, 9, 9, 7, 8, 12},	// 2  Less Open
	{10, 9, 9, 9, 9, 7, 8, 12},	// 3  Heredoc Open
	{10, 9, 9, 5, 9, 7, 8, 12},	// 4  Greater Open
	{10, 9, 9, 9, 9, 7, 8, 12},	// 5  Append Open
	{11, 9, 9, 9, 9, 7, 8, 12},	// 6  & Found
	{7, 7, 7, 7, 7, 11, 7, 7},	// 7  Open double quotes
	{8, 8, 8, 8, 8, 8, 11, 8},	// 8  Open single quotes
	{9, 9, 9, 9, 9, 9, 9, 9},	// 9  Invalid input
	{10, 9, 9, 9, 9, 7, 8, 12},	// 10 Spaces after key
	{11, 1, 2, 4, 6, 7, 8, 12},	// 11 Spaces between words
	{11, 1, 2, 4, 6, 7, 8, 12},	// 12 Comands
	};

	return (states[i][j]);
}

//   \s, ", ', <, >, ^

int	tokenizer_get_state(int i, int j)
{
	const int	states[][8] = {
	{0, 1, 2, 6, 8, 10},	// 0 Empty input
	{1, 5, 1, 1, 1, 1},		// 1 Open double quotes
	{2, 2, 5, 2, 2, 2},		// 2 Open single quotes
	{3, 3, 3, 3, 3, 3},		// 3 Invalid input
	{4, 1, 2, 6, 8, 10},	// 4 Spaces without words
	{5, 1, 2, 6, 8, 10},	// 5 Spaces between words
	{4, 1, 2, 7, 8, 10},	// 6 lower found
	{4, 1, 2, 3, 3, 10},	// 7 heredoc
	{4, 1, 2, 3, 9, 10},	// 8 greater found
	{4, 1, 2, 3, 3, 10},	// 9 append
	{5, 1, 2, 6, 8, 10},	// 10 Not operators
	};

	return (states[i][j]);
}

int	idx(char *alphabet[], char c)
{
	int	i;

	i = -1;
	while (alphabet[++i])
		if (ft_chrpos(alphabet[i], c) != -1)
			return (i);
	return (i);
}

int	evaluate(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < (int)ft_strlen(a->str))
	{
		a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
		if (a->fsa[a->state])
			a->fsa[a->state](a, a->data);
		if (a->fta[a->ostate][a->state])
			a->fta[a->ostate][a->state](a, a->data);
		a->ostate = a->state;
	}
	return (a->state);
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
