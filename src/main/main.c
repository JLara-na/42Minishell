/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:40:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/14 00:49:16 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
void	prueba(void)
{
	int		fd[2];
	pid_t	pid;
	char	buffer[130];
	int		x;

	x = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]); // close the read end of the pipe
		x = write(fd[1], "Hello parent!", 13);
		close(fd[1]); // close the write end of the pipe
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		close(fd[1]); // close the write end of the pipe
		x = read(fd[0], buffer, 13);
		close(fd[0]); // close the read end of the pipe
		printf("Message from child: '%s'\n", buffer);
	}
	printf("x : %d\n", x);
}
*/
/*
void	get_tokens(t_shell *shell)
{
	int	i;

	i = -1;
	shell->tokens = ft_split(shell->checker.str, '|');
	printf("tokens:\n");
	while (shell->tokens[++i])
		printf("[%s]\n", shell->tokens[i]);
	i = -1;
	while (shell->tokens[++i])
		free(shell->tokens[i]);
	free(shell->tokens);
	return ;
}*/

void	init_hell(t_shell	*shell, char **envp)
{
	printf(CLEAR HEADER);
	ft_bzero(shell, sizeof(t_shell));
	get_env(shell, envp);
}

void	free_token(void	*data)
{
	t_token	*token;

	token = data;
	free(token->line);
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

	token = (t_token *)data;
	printf("token line-> [%s]\n", token->line);
}
//--------------------------------------------------------

void	main_loop(t_shell	*shell)
{

	while (1)
	{
		if (split_in_token_lines(shell))
		{
			ft_tree_in_order_arg(shell->token_tree, tokenize_node, shell);
			if (ft_strnstr(shell->splitter.str, "exit", ft_strlen(shell->splitter.str))
				&& ft_strlen(shell->splitter.str) == 4)
				break ;

		}
		ft_tree_in_order(shell->token_tree, print_tree);
		free_tree(shell, shell->token_tree);
		free(shell->splitter.str);
	}
	free(shell->splitter.str);
	free_tree(shell, shell->token_tree);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_hell(&shell, envp);
	main_loop(&shell);
	free_env(&shell);
	printf(MSG_BYE);
	return (0);
}
