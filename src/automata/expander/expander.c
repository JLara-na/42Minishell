/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:47:38 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/01 21:59:13 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	expand_line(t_token	*token, t_shell	*shell, char	**str)
{
	token->data = str;
	expander_automata_init(&shell->expander, token);
	shell->expander.str = ft_strdup(*str);
	free(*str);
	*str = ft_strdup("");
	evaluate(&shell->expander);
	free(shell->expander.str);
	free_alph_err(&shell->expander);
}

void	expand_token(void	*token_ptr, void	*shell_ptr)
{
	t_shell	*shell;
	t_token	*token;
	int		i;

	shell = (t_shell *)shell_ptr;
	token = (t_token *)token_ptr;
	if (token->cmd)
		expand_line(token, shell, &token->cmd);
	i = 0;
	if (token->args)
		while (token->args[i])
			expand_line(token, shell, &token->args[i++]);
	i = 0;
	if (token->outfiles)
		while (token->outfiles[i])
			expand_line(token, shell, &token->outfiles[i++]);
	i = 0;
	if (token->infiles)
		while (token->infiles[i])
			expand_line(token, shell, &token->infiles[i++]);
}
