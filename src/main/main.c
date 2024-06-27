/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:40:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/06/28 00:36:13 by jlara-na         ###   ########.fr       */
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

void	get_tokens(t_shell *shell)
{
	int	i;

	i = -1;
	shell->tokens = ft_split(shell->a.str, '|');
	printf("tokens:\n");
	while (shell->tokens[++i])
		printf("[%s]\n", shell->tokens[i]);
	i = -1;
	while (shell->tokens[++i])
		free(shell->tokens[i]);
	free(shell->tokens);
	return ;
}

int	check_valid(t_shell	*shell)
{
	int	a_state;

	automata_init(&shell->a, shell);
	shell->a.str = readline(CUSTOM_2 M_SHELL_PROMPT DEF_COLOR);
	add_history(shell->a.str);
	a_state = evaluate(&shell->a);
	if (a_state > shell->a.errorlen)
	{
		get_tokens(shell);
		return (free_alph_err(&shell->a), 1);
	}
	else
	{
		printf(RED "%s\n" DEF_COLOR, shell->a.errors[a_state]);
		return (free_alph_err(&shell->a), 0);
	}
}

void	main_loop(t_shell	*shell)
{
	while (1)
	{
		check_valid(shell);
		if (ft_strnstr(shell->a.str, "exit", ft_strlen(shell->a.str))
			&& ft_strlen(shell->a.str) == 4)
			break ;
		free(shell->a.str);
		shell->a.str = NULL;
	}
	free(shell->a.str);
	shell->a.str = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	printf(CLEAR HEADER);
	get_env(&shell, env);
	built_in_env(&shell);
	main_loop(&shell);
	free_env(&shell);
	printf(MSG_BYE);
}
