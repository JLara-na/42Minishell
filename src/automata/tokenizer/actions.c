/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/14 00:48:13 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// CONTINUAR CON ESTAS ACCIONES PARA GUARDAR LOS DATOS DEL TOKEN

void	set_infile(t_automata	*a, void	*data)
{
	t_shell	*shell;

	shell = (t_shell *)data;
	(void)a;
	(void)shell;
	printf(CUSTOM_1 "INFILE LOCALIZADO\n" DEF_COLOR);
}

void	set_outfile(t_automata	*a, void	*data)
{
	t_shell	*shell;

	shell = (t_shell *)data;
	(void)a;
	(void)shell;
	printf(CUSTOM_3 "OUTFILE LOCALIZADO\n" DEF_COLOR);
}
/*
void	set_cmd_and_args(t_automata	*a, void	*data)
{
	t_shell	*shell;

	shell = (t_shell *)data;
}
*/