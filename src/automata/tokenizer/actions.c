/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/30 21:25:41 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// FT UTILS FOR THE ACTIONS

int	arg_length(char	*arg)
{
	int	len;

	len = 0;
	if (arg[0] == '\"' || arg[0] == '\'')
	{
		len++;
		while (arg[len] != arg[0])
			len++;
		len++;
	}
	else
		while ((arg[len] != ' ' && arg[len] != '\t' && arg[len] != '\n'
				&& arg[0]) && arg[len] != '\0')
			len++;
	return (len);
}

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
	i = arg_length(trm);
	next_word = ft_substr(trm, 0, i);
	free(trm);
	return (next_word);
}

// FT ACTIONS

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

void	set_cmd_and_args(t_automata	*a, void	*data)
{
	t_token		*token;
	char		*arg;
	static int	i;

	token = (t_token *)data;
	arg = get_next_word(a);
	token->args = ft_add_to_sarray(token->args, arg);
	if (i == 0)
		token->cmd = ft_strdup(arg);
	i++;
	free(arg);
}
