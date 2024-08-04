/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:18:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/04 19:31:39 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
/*
t_token	*create_new_token(char	*line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->line = line;
	return (token);
}

void	add_new_token(t_tree	*tree, char	*line)
{
	if (!tree->left)
	{
		tree->left = ft_tree_create_node(tree->data);
		tree->data = create_new_token(line);
	}
	else if (!tree->right)
		tree->right = ft_tree_create_node(create_new_token(line));
	else
		add_new_token(tree->right, line);
}

void	get_string(t_automata *a, void *data)
{
	t_shell	*shell;
	char	*substr;
	char	*trim;

	shell = (t_shell *)data;
	substr = ft_substr(a->str, a->j, a->i - a->j);
	trim = ft_strtrim(substr, " ");
	free(substr);
	a->j = a->i;
	printf("Line %s", shell->expanded_line);
	if (!shell->expanded_line)
		shell->expanded_line = trim;
	else
		shell->expanded_line = ft_strjoinfree(shell->expanded_line, trim, 2);
}

void	get_token(t_automata *a, void *data)
{
	t_shell	*shell;

	get_string(a, data);
	shell = (t_shell *)data;
	if (!shell->token_tree)
		shell->token_tree = ft_tree_create_node(create_new_token(shell->expanded_line));
	else
		add_new_token(shell->token_tree, shell->expanded_line);
	free (shell->expanded_line);
	shell->expanded_line = NULL;
}

 void	save_line(t_automata *a, void *data)
{
	t_shell	*shell;
	//t_token	*token;
	token = (t_token *)shell->current_node->data;

	(void)a;
	shell = (t_shell *)data;
	add_new_token(shell->token_tree, NULL);
	shell->current_node = shell->token_tree->left;
	get_token(a, shell);
} 


void	expand_var(t_automata	*a, void	*data)
{
	(void)data;
	get_string(a, data);
	if (a->ostate == SP_DOUBLEQ)
		a->state = SP_DOUBLEQ;
	printf(RED "expand var\n" DEF_COLOR);
}
*/

t_token	*create_new_token(char	*line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->line = line;
	return (token);
}

void	add_new_token(t_tree	*tree, char	*line)
{
	if (!tree->left)
	{
		tree->left = ft_tree_create_node(tree->data);
		tree->data = create_new_token(line);
	}
	else if (!tree->right)
		tree->right = ft_tree_create_node(create_new_token(line));
	else
		add_new_token(tree->right, line);
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
		shell->token_tree = ft_tree_create_node(create_new_token(trim));
	else
		add_new_token(shell->token_tree, trim);
}
