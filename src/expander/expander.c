/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:47:38 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/19 21:16:30 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
	int j;

	j = 0;
	while (str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '$' && str[i + j] != '\0')
		j++;
	var = ft_substr(str, i, j);
	printf(BLUE "var->[%s]\n" DEF_COLOR, var);
	free(var);
*/

char	*var_expander(char *str, int start, int len)
{
	
}

void	expand_vars(char	*str)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 1;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '$')
		{
			while (str[i + j] != '\0' && str[i + j] != ' ' && str[i + j]
				!= '\'' && str[i + j] != '\"' && str[i + j] != '$')
				j++;
			var = var_expander(str, i, j);
			printf(BLUE "var->[%s]\n" DEF_COLOR, var);
			free(var);
		}
		i++;
	}
}

void	expand_node(void	*data, void	*arg)
{
	t_token	*token;
	t_shell	*shell;

	token = (t_token *)data;
	shell = (t_shell *)arg;
	(void)arg;
	(void)shell;
	expand_vars(token->line);

}

void	ft_expander(t_shell	*shell)
{
	ft_tree_in_order_arg(shell->token_tree, expand_node, shell);
}
