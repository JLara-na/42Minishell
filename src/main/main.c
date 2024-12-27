/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:40:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/27 15:21:18 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_signal_data = 0;

char	*generate_prompt(void)
{
	char	*prompt;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	prompt = NULL;
	prompt = ft_strjoinfree(CUSTOM_208 M_SHELL_PROMPT CUSTOM_87 "~", pwd, 1);
	prompt = ft_strjoinfree(prompt, CUSTOM_208 "> " DEFAULT_SGR, 0);
	return (prompt);
}

void	init_hell(t_shell	*shell, char **envp)
{
	g_signal_data = 0;
	set_sig_handler(standard_handler, 0);
	printf(HEADER);
	ft_bzero(shell, sizeof(t_shell));
	import_env(shell, envp);
}

void	free_token(void	*data)
{
	t_token	*token;

	token = data;
	free(token->line);
	free(token->cmd);
	if (token->args)
		ft_free_sarray(token->args);
	if (token->outfiles)
		ft_free_sarray(token->outfiles);
	if (token->infiles)
		ft_free_sarray(token->infiles);
	if (token->heredoc)
		ft_free_sarray(token->heredoc);
	free(token);
}

void	free_tree(t_shell	*shell, t_tree	*tree)
{
	if (tree != NULL)
	{
		free_tree(shell, tree->left);
		free_token(tree->data);
		free_tree(shell, tree->right);
		free(tree);
		shell->token_tree = NULL;
	}
}
//---------------------- TREE FTS-------------------------

void	print_tree(void *data)
{
	t_token	*token;
	int		i;

	i = 0;
	token = (t_token *)data;
	printf(YELLOW "NEW TOKEN\n" DEFAULT_SGR);
	printf("token str->[%s]\n", token->line);
	if (token->cmd)
		printf("cmd->(%s)\n", token->cmd);
	if (token->args)
		while (token->args[i])
			printf(CUSTOM_101 "args->(%s)\n" DEFAULT_SGR, token->args[i++]);
	i = 0;
	if (token->outfiles)
		while (token->outfiles[i])
			printf("outfiles->(%s)\n", token->outfiles[i++]);
	i = 0;
	if (token->infiles)
		while (token->infiles[i])
			printf("infiles->(%s)\n", token->infiles[i++]);
}
//--------------------------------------------------------

void	main_loop(t_shell	*shell)
{
	while (1)
	{
		g_signal_data = 0;
		if (split_in_token_lines(shell))
		{
			set_sig_handler(SIG_IGN, 0);
			ft_tree_in_order_arg(shell->token_tree, tokenize_node, shell);
			if (g_signal_data != SIGINT)
			{
				ft_tree_in_order_arg(shell->token_tree, expand_token, shell);
				set_sig_handler(SIG_IGN, 0);
				exe_minishell_recursive(shell->token_tree);
			}
			ft_tree_in_order_arg(shell->token_tree, unlink_heredocs, shell);
			//printf("Exit Status %d\n", shell->exit_status);
			// ft_tree_in_order(shell->token_tree, print_tree);
		}
		printf(RED "%d\n" DEFAULT_SGR, g_signal_data);
		free_tree(shell, shell->token_tree);
		free(shell->splitter.str);
		set_sig_handler(standard_handler, 0);
	}
	free(shell->splitter.str);
	free_tree(shell, shell->token_tree);
	free_env(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_hell(&shell, envp);
	main_loop(&shell);
	printf(MSG_BYE);
	return (EXIT_SUCCESS);
}
