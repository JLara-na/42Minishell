/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:07 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/27 23:39:09 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*

	AUTOMATA STATES MATRIX

const int states[][4] = {
	" ",  |,  <,  >,  &,  ",  ',
	{ 0, 11, 11, 11, 11,  1,  2, 14},   // 0  Empty input
	{ 1,  1,  1,  1,  1, 13,  1,  1},   // 1  Open double quotes
	{ 2,  2,  2,  2,  2,  2, 13,  2},   // 2  Open single quotes
	{12,  4,  5, 11, 11,  1,  2, 14},   // 3  Pipe open
	{12, 11, 11, 11, 11,  1,  2, 14},   // 4  Or open
	{12, 11,  6, 11, 11,  1,  2, 14},   // 5  Less open
	{12, 11, 11, 11, 11,  1,  2, 14},   // 6  Heredoc open
	{12, 11, 11,  8, 11,  1,  2, 14},   // 7  Greater open
	{12, 11, 11, 11, 11,  1,  2, 14},   // 8  Append open
	{12, 11, 11, 11, 10,  1,  2, 11},   // 9  & Found
	{12, 11, 11, 11, 11,  1,  2, 14},   // 10 And open
	{11, 11, 11, 11, 11, 11, 11, 11},   // 11 Invalid input
	{12,  1,  1,  1,  1,  1,  2, 14},   // 12 Spaces without words
	{13,  3,  5,  7,  9,  1,  2, 14},   // 13 Spaces between words
	{13,  3,  5,  7,  9,  1,  2, 14},   // 14 Not operators
	};
	
	const int	states[][8] = {
	" ",  |,  <,  >,  &,  ",  ',  C
	{0, 9, 9, 9, 9, 7, 8, 12},	// 0  Empty
	{11, 9, 2, 4, 9, 7, 8, 12},	// 1  Pipe Open (NO CONTEMPLAMOS OR)
	{11, 9, 3, 9, 9, 7, 8, 12},	// 2  Less Open
	{11, 9, 9, 9, 9, 7, 8, 12},	// 3  Heredoc Open
	{11, 9, 9, 5, 9, 7, 8, 12},	// 4  Greater Open
	{11, 9, 9, 9, 9, 7, 8, 12},	// 5  Append Open
	{11, 9, 9, 9, 9, 7, 8, 12},	// 6  & Found
	{7, 7, 7, 7, 7, 10, 7, 7},	// 7  Open double quotes
	{8, 8, 8, 8, 8, 8, 10, 8},	// 8  Open single quotes
	{9, 9, 9, 9, 9, 9, 9, 9},	// 9  Invalid input
	{10, 1, 2, 4, 6, 7, 8, 12},	// 10 Spaces between words
	{11, 7, 7, 7, 7, 7, 8, 12},	// 11 Spaces without words
	{10, 1, 2, 4, 6, 7, 8, 12},	// 12 Comands
	};
	

int	get_state(int i, int j)
{
	const int	states[][8] = {
	{ 0,  9,  9,  9,  9,  7,  8, 12},	// 0  Empty
	{10,  9,  9,  9,  9,  7,  8, 12},	// 1  Pipe Open (NO CONTEMPLAMOS OR)
	{10,  9,  3,  9,  9,  7,  8, 12},	// 2  Less Open
	{10,  9,  9,  9,  9,  7,  8, 12},	// 3  Heredoc Open
	{10,  9,  9,  5,  9,  7,  8, 12},	// 4  Greater Open
	{10,  9,  9,  9,  9,  7,  8, 12},	// 5  Append Open
	{11,  9,  9,  9,  9,  7,  8, 12},	// 6  & Found
	{ 7,  7,  7,  7,  7, 11,  7,  7},	// 7  Open double quotes
	{ 8,  8,  8,  8,  8,  8, 11,  8},	// 8  Open single quotes
	{ 9,  9,  9,  9,  9,  9,  9,  9},	// 9  Invalid input
	{10,  9,  9,  9,  9,  7,  8, 12},	// 10 Spaces after key
	{11,  1,  2,  4,  6,  7,  8, 12},	// 11 Spaces between words
	{11,  1,  2,  4,  6,  7,  8, 12},	// 12 Comands
	};

	return (states[i][j]);
}
*/

int	get_state(int i, int j)
{
	const int	states[][8] = {
	{0, 9, 9, 9, 9, 7, 8, 12},	// 0  Empty
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

void	automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	alphabet_init(a);
	errors_init(a);
	sactions_init(a);
	tactions_init(a);
	a->get_state = get_state;
}

int	ft_chrpos(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
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
