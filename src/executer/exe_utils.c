/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:42:25 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/18 21:30:10 by jlara-na         ###   ########.fr       */
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

/*void	stdin_redirection(t_token	*token, int fd[2])
{
	
}*/

void	child_pipe_redir(t_tree *node, t_token *token, int pid, int fd[2])
{
	pid = fork();
    if (!pid)
	{
		//HAZ EL DUP AL PIPE O A LA REDIRECCION
		dup2(fd[WRITE_END], STDOUT_FILENO);
		//COMPROBAR REDIRECCIONES AQUI
		close(fd[READ_END]);
		token->shell->child = 1;
		exe_minishell_recursive(node->left);
	}
	else
	{
		pid = fork();
		if (!pid)
		{
			//HAZ EL DUP AL PIPE O A LA REDIRECCION
			dup2(fd[READ_END], STDIN_FILENO);
			//COMPROBAR REDIRECCIONES AQUI
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
			exe_built_in(token, token->shell); // HACER AQUI LAS REDIRECCIONES PARA LOS BUILT INS SIN PIPES
		}
		else
		{
			pid = fork();
			if (!pid)
			{
				stdout_redirection(token);
				exe_path_cmd(token->shell, token);
			}
			wait_childs(token, FALSE);
		}
	}
	else
	{
		stdout_redirection(token);
		exe_cmd_or_built(token->shell, token);
	}
}
