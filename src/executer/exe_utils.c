/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:42:25 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/26 01:25:16 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	stdout_redirection(t_token	*token)
{
	int	i;

	i = -1;
	token->last_outf_fd = -1;
	if (token->outfiles)
	{
		while (token->outfiles[++i])
		{
			if (token->append)
				token->last_outf_fd = open(token->outfiles[i],
						O_CREAT | O_APPEND | O_WRONLY, 0644);
			else
				token->last_outf_fd = open(token->outfiles[i],
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (token->outfiles[i + 1])
				close(token->last_outf_fd);
		}
	}
	if (token->last_outf_fd != -1)
		dup2(token->last_outf_fd, STDOUT_FILENO);
}

int	is_heredoc(t_token	*token, char	*str)
{
	int	i;

	if (!token->heredoc)
		return (0);
	i = -1;
	while (token->heredoc[++i])
	{
		if (ft_samestr(str, token->heredoc[i]))
			return (1);
	}
	return (0);
}

int	do_heredoc(char *str, t_token	*token)
{
	char	*line;
	int		fd;

	fd = open(/*".heredoc_temp_file"*/str,
			O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		printf("OPEN ERROR\n");
		return (fd);
	}
	line = readline(BLUE ">" DEFAULT_SGR);
	while (line && (!ft_samestr(str, line)))
	{
		expand_line(token, token->shell, &line);
		if (write(fd, line, ft_strlen(line)))
			if (write(fd, "\n", 1))
				free(line);
		line = readline(BLUE ">" DEFAULT_SGR);
	}
	free(line);
	close(fd);
	fd = open(".heredoc_temp_file", O_RDONLY);
	return (fd);
}

void	stdin_redirection(t_token	*token)
{
	int	i;

	i = -1;
	token->last_inf_fd = -1;
	if (token->infiles)
	{
		while (token->infiles[++i])
		{
			if (is_heredoc(token, token->infiles[i]))
				token->last_inf_fd = do_heredoc(token->infiles[i], token);
			else
			{
				if (access(token->infiles[i], R_OK))
					return (perror(token->infiles[i]), exit(1));
				token->last_inf_fd = open(token->infiles[i], O_RDONLY);
			}
			if (token->infiles[i + 1])
				close(token->last_inf_fd);
		}
	}
	if (token->last_inf_fd != -1)
	{
		dup2(token->last_inf_fd, STDIN_FILENO);
		close(token->last_inf_fd);
	}
}

void	stdin_stdout_reset(t_token	*token)
{
	int	fd_out;
	int	fd_in;

	(void)token;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	dup2(STDIN_FILENO, token->last_inf_fd);
	dup2(STDOUT_FILENO, token->last_outf_fd);
	close(fd_in);
	close(fd_out);
}


void	child_pipe_redir(t_tree *node, t_token *token, int pid, int fd[2])
{
	pid = fork();
	if (!pid)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[READ_END]);
		token->shell->child = 1;
		exe_minishell_recursive(node->left);
	}
	else
	{
		pid = fork();
		if (!pid)
		{
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[WRITE_END]);
			token->shell->child = 1;
			exe_minishell_recursive(node->right);
		}
	}
	
	close(fd[WRITE_END]);
	close(fd[READ_END]);
}

void	exe_comand_node(t_token	*token, int pid)
{
	if (!token->shell->child)
	{
		if (is_built_in(token->cmd))
		{
			stdin_redirection(token);
			stdout_redirection(token);
			exe_built_in(token, token->shell); // AQUI RED BUILT INS SIN PIPES
			stdin_stdout_reset(token);
		}
		else
		{
			pid = fork();
			if (!pid)
			{
				stdin_redirection(token);
				stdout_redirection(token);
				exe_path_cmd(token->shell, token);
			}
			wait_childs(token, FALSE);
		}
	}
	else
	{
		stdin_redirection(token); // REVISAR EL USO DE HEREDOC CUANDO HAY PIPES
		stdout_redirection(token);
		exe_cmd_or_built(token->shell, token);
	}
}
