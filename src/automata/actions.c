/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/28 00:48:23 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* ************************************************************************** */
/*    This file will contain all the custom actions refered to the project    */
/* ************************************************************************** */

/*void	getnum(t_automata *a, void *data)
{
	int			nb;
	static int	index;
	t_blist		**stack_one;

	stack_one = (t_blist **)data;
	nb = ft_atoi(a->str + a->j);
	ft_blstadd_back(stack_one, ft_blstnew(nb, index));
	index++;
	a->j = a->i;
}

void	negative_alone(t_automata *a, void *data)
{
	(void)data;
	if (a->str[a->i + 1] == '\0' || a->str[a->i + 1] == ' ')
		parsing_error(a, NULL);
}
*/
void	funcion(t_automata *a, void *data)
{
	(void)a;
	(void)data;
}
