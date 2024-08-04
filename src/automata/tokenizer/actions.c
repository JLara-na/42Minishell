/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/04 22:21:27 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

void	set_arg(t_automata	*a, void	*data)
{
	t_token		*token;
	char		*arg;

	token = (t_token *)data;
	arg = get_next_word(a);
	token->args = ft_add_to_sarray(token->args, arg);
	if (!token->cmd)
		token->cmd = ft_strdup(arg);
	free(arg);
}