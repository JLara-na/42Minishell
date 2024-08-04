/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:47:38 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/03 17:20:28 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/* 
int	looking_for_dollars(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' || str[i] != '\0')
				i++;
		}
		else if (str[i] == '$')
			return (i);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

char	*expand_next_var(char	*str, char	**env)
{
	char	*env_var;
	//char	*new_str;
	int		dollar;
	int		space;

	(void)env;
	env_var = NULL;
	//new_str = NULL;
	dollar = looking_for_dollars(str);
	space = dollar;
	printf("shit -> %d\n", dollar);
	while (str[space] != '\0')
	{
		printf("shit");
		space++;
	env_var = ft_substr(str, dollar, space);
	printf("variable-> %s\n", env_var);
	//free(env_var);
	return (env_var);
}

void	expand_vars(char	**str, t_shell	*shell)
{
	char	*new_str;

	new_str = NULL;
	//while (looking_for_dollars(new_str))
		new_str = expand_next_var(str[0], shell->local_env);
	free(*str);
	*str = ft_strdup(new_str);
}

void	expand_node(void	*data, void	*arg)
{
	t_token	*token;
	t_shell	*shell;
	//int		i;

	token = (t_token *)data;
	shell = (t_shell *)arg;
	//i = 0;
	if (token->cmd)
		expand_vars(&token->cmd, shell);
	if (token->args)
		while (token->args[i])
			expand_vars(token->args[i++], shell);
	if (token->outfiles)
		while (token->outfiles[i])
			expand_vars(token->outfiles[i++], shell);
	if (token->infiles)
		while (token->infiles[i])
			expand_vars(token->infiles[i++], shell);
}

void	ft_expander(t_shell	*shell)
{
	ft_tree_in_order_arg(shell->token_tree, expand_node, shell);
}
 */