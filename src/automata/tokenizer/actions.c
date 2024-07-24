/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/24 21:44:50 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// CONTINUAR CON ESTAS ACCIONES PARA GUARDAR LOS DATOS DEL TOKEN

char	*get_next_word(t_automata	*a)
{
	char	*substr;
	char	*trm;
	char	*next_word;
	int		i;

	i = 0;
	while (a->str[a->i + i] != '<' && a->str[a->i + i] != '>'
		&& a->str[a->i + i] != '\0')
		i++;
	substr = ft_substr(a->str, a->i, i);
	a->j = a->i;
	trm = ft_strtrim(substr, " ");
	free(substr);
	i = 0;
	while (trm[i] != ' ' && trm[i] != '\t' && trm[i] != '\n' && trm[i] != '\0')
		i++;
	if (trm[0] == '\"' || trm[0] == '\'')
		next_word = trm;
	else
		next_word = ft_substr(trm, 0, i);
	free(trm);
	return (next_word);
}

void	set_infile(t_automata	*a, void	*data)
{
	t_token	*token;
	char	*infile;

	token = (t_token *)data;
	infile = get_next_word(a);
	if (a->ostate == TK_HEREDOC)
	{
		token->infiles = ft_add_to_sarray(token->infiles, "");
		token->heredoc = TRUE;
	}
	else
		token->infiles = ft_add_to_sarray(token->infiles, infile);
	free(infile);
}

void	set_outfile(t_automata	*a, void	*data)
{
	t_token	*token;
	char	*outfile;

	token = (t_token *)data;
	outfile = get_next_word(a);
	token->outfiles = ft_add_to_sarray(token->outfiles, outfile);
	if (a->ostate == TK_APPEND)
		token->append = TRUE;
	else
		token->append = FALSE;
	free(outfile);
}
/*
void	set_cmd_and_args(t_automata	*a, void	*data)
{
	t_shell	*shell;

	shell = (t_shell *)data;
}
*/