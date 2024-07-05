/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:40:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/05 23:07:32 by jlara-na         ###   ########.fr       */
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

void	tokenizer(t_shell *shell)
{
	int	a_state;

	tokenizer_automata_init(&shell->tokenizer, shell);
	shell->tokenizer.str = shell->checker.str;
	a_state = evaluate(&shell->tokenizer);
	get_token(&shell->tokenizer, shell);
	printf(BLUE "%d\n" DEF_COLOR, a_state);
	free_alph_err(&shell->tokenizer);
}

int	check_valid(t_shell	*shell)
{
	int	a_state;

	checker_automata_init(&shell->checker, shell);
	shell->checker.str = readline(CUSTOM_2 M_SHELL_PROMPT DEF_COLOR);
	add_history(shell->checker.str);
	a_state = evaluate(&shell->checker);
	if (a_state > shell->checker.errorlen)
		return (free_alph_err(&shell->checker), 1);
	else
	{
		printf(RED "%s\n" DEF_COLOR, shell->checker.errors[a_state]);
		return (free_alph_err(&shell->checker), 0);
	}
}

void	print_tree(void *data)
{
	
	// ME QUEDE AQUI, HAY QUE IMPRIMIR EL ARBOL PARA VER SI SE HA GUARDADO CORRECTAMENTE
}

void	main_loop(t_shell	*shell)
{
	while (1)
	{
		if (check_valid(shell))
		{
			tokenizer(shell);
			ft_tree_in_order(shell->token_tree, print_tree); // <---- LO IMPRIMO AQUI




			if (ft_strnstr(shell->checker.str, "exit", ft_strlen(shell->checker.str))
			&& ft_strlen(shell->checker.str) == 4)
				break ;




		}
		free(shell->checker.str);
	}
	free(shell->checker.str);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	printf(CLEAR HEADER);
	get_env(&shell, envp);
	main_loop(&shell);
	free_env(&shell);
	printf(MSG_BYE);
	return (0);
}
