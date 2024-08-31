/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_matrices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:28:01 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/28 20:49:39 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	0	1	2	3	4	5	6	Column characters
//	\s	|	<	>	"	'	^
int	splitter_get_state(int i, int j)
{
	const int	states[][7] = {
	{0, 8, 2, 4, 6, 7, 11},		// 0  Empty
	{9, 8, 8, 8, 6, 7, 11},		// 1  Pipe Open (NO CONTEMPLAMOS OR)
	{9, 8, 3, 8, 6, 7, 11},		// 2  Less Open
	{9, 8, 8, 8, 6, 7, 11},		// 3  Heredoc Open
	{9, 8, 8, 5, 6, 7, 11},		// 4  Greater Open
	{9, 8, 8, 8, 6, 7, 11},		// 5  Append Open
	{6, 6, 6, 6, 10, 6, 6},		// 6  Open double quotes
	{7, 7, 7, 7, 7, 10, 7},		// 7  Open single quotes
	{8, 8, 8, 8, 8, 8, 8},		// 8  Invalid input
	{9, 8, 8, 8, 6, 7, 11},		// 9 Spaces after key
	{10, 1, 2, 4, 6, 7, 11},	// 10 Spaces between words
	{10, 1, 2, 4, 6, 7, 11},	// 11 Comands
	};

	return (states[i][j]);
}
/*
//	0	1	2   3	4	Column characters
//	"	'   $   /s
int	expander_get_state(int i, int j)
{
	const int	states[][8] = {
	{1, 2, 3, 0},	// 0 Looking
	{0, 1, 4, 1},	// 1 Open double quotes
	{2, 0, 2, 2},	// 2 Open single quotes
	{1, 2, 3, 0},	// 3 Dollar outside
	{0, 1, 4, 1},	// 4 Dollar inside 
	{0, 0, 0, 0},	// 5 Name	outside
	{0, 0, 0, 0},	// 6 Name	inside
	};

	return (states[i][j]);
}*/

//	0	1	2   3	4	Column characters
//	/s	"   '	$   ^
int	expander_get_state(int i, int j)
{
	const int	states[][5] = {
	{0, 1, 2, 3, 0},	// 0 Looking
	{1, 0, 1, 4, 1},	// 1 Open double quotes
	{2, 2, 0, 2, 2},	// 2 Open single quotes
	{0, 1, 2, 3, 5},	// 3 Dollar outside
	{1, 0, 1, 4, 6},	// 4 Dollar inside 
	{0, 1, 2, 3, 5},	// 5 Name	outside
	{1, 0, 1, 4, 6},	// 6 Name	inside
	};

	return (states[i][j]);
}

//	0	1	2	3	4	5	Column characters
//  \s	"	'	<	>	^
int	tokenizer_get_state(int i, int j)
{
	const int	states[][6] = {
	{0, 1, 2, 6, 8, 10},	// 0 Empty input
	{1, 11, 1, 1, 1, 1},	// 1 Open double quotes
	{2, 2, 11, 2, 2, 2},	// 2 Open single quotes
	{3, 3, 3, 3, 3, 3},		// 3 Invalid input
	{4, 1, 2, 6, 8, 10},	// 4 Spaces without words
	{5, 1, 2, 6, 8, 10},	// 5 Spaces between words
	{4, 1, 2, 7, 8, 10},	// 6 lower found
	{4, 1, 2, 3, 3, 10},	// 7 heredoc
	{4, 1, 2, 3, 9, 10},	// 8 greater found
	{4, 1, 2, 3, 3, 10},	// 9 append
	{5, 1, 2, 6, 8, 10},	// 10 Not operators
	{5, 1, 2, 6, 8, 10},	// 11 End of q
	};

	return (states[i][j]);
}
