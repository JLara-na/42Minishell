/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/17 00:50:46 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// CONTINUAR CON ESTAS ACCIONES PARA GUARDAR LOS DATOS DEL TOKEN

char	*get_next_word(t_automata	*a)
{
	char	*substr;
	char	*next_word;
	int		i;

	i = 0;
	while (a->str[a->i + i] != '<' && a->str[a->i + i] != '>' && a->str[a->i + i] != '\0')
		i++;
	substr = ft_substr(a->str, a->i, i);
	a->j = a->i;
	next_word = ft_strtrim(substr, " ");
	free(substr);
	return (next_word);
}

void	set_infile(t_automata	*a, void	*data)
{
	t_token	*token;

	token = (t_token *)data;
	(void)token;
	if (a->str[a->i + 1] == '<')
		printf(CUSTOM_1 "HEREDOC LOCALIZADO\n" DEF_COLOR);
	else
		printf(CUSTOM_1 "INFILE LOCALIZADO\n" DEF_COLOR);
}

void	set_outfile(t_automata	*a, void	*data)
{
	t_token	*token;
	char	*outfile;


	token = (t_token *)data;
	if (a->str[a->i + 1] == '>')
		token->append = TRUE;
	else
		token->append = FALSE;
	outfile = get_next_word(a);
	token->outfiles = ft_add_to_sarray(token->outfiles, outfile);
	free(outfile);
}

/*
void	set_cmd_and_args(t_automata	*a, void	*data)
{
	t_shell	*shell;

	shell = (t_shell *)data;
}
*/