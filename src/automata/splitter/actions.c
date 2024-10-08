/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/28 20:19:59 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_token	*create_new_token(char	*line, t_shell	*shell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->shell = shell;
	token->line = line;
	return (token);
}

void	add_new_token(t_tree	*tree, char	*line, t_shell	*shell)
{
	if (!tree->left)
	{
		tree->left = ft_tree_create_node(tree->data);
		tree->data = create_new_token(line, shell);
	}
	else if (!tree->right)
		tree->right = ft_tree_create_node(create_new_token(line, shell));
	else
		add_new_token(tree->right, line, shell);
}

void	get_token(t_automata *a, void *data)
{
	t_shell	*shell;
	char	*substr;
	char	*trim;

	shell = (t_shell *)data;
	substr = ft_substr(a->str, a->j, a->i - a->j);
	trim = ft_strtrim(substr, " ");
	free(substr);
	a->j = a->i;
	if (!shell->token_tree)
		shell->token_tree = ft_tree_create_node(create_new_token(trim, shell));
	else
		add_new_token(shell->token_tree, trim, shell);
}
