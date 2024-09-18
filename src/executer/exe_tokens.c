/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:36:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/18 21:29:20 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(char	*cmd)
{
	if (ft_samestr(cmd, CD_BUILT))
		return (1);
	if (ft_samestr(cmd, ECHO_BUILT))
		return (1);
	if (ft_samestr(cmd, ENV_BUILT))
		return (1);
	if (ft_samestr(cmd, EXIT_BUILT))
		return (1);
	if (ft_samestr(cmd, EXPORT_BUILT))
		return (1);
	if (ft_samestr(cmd, PWD_BUILT))
		return (1);
	if (ft_samestr(cmd, UNSET_BUILT))
		return (1);
	return (0);
}

int	exe_built_in(void	*data, void	*context)
{
	t_token	*token;
	t_shell	*shell;

	token = (t_token *)data;
	shell = (t_shell *)context;
	if (ft_samestr(token->cmd, CD_BUILT))
		return (-1);
	if (ft_samestr(token->cmd, ECHO_BUILT))
		return (-1);
	if (ft_samestr(token->cmd, ENV_BUILT))
		return (built_in_env(shell));
	if (ft_samestr(token->cmd, EXIT_BUILT))
		return (-1);
	if (ft_samestr(token->cmd, EXPORT_BUILT))
		return (built_in_export(shell, token));
	if (ft_samestr(token->cmd, PWD_BUILT))
		return (built_in_pwd(shell));
	if (ft_samestr(token->cmd, UNSET_BUILT))
		return (-1);
	return (1);
}

int	set_exit_status(char	*cmd, int error_number)
{
	perror(cmd);
	if (error_number == EACCES)
		return (ESCAPE_126);
	if (error_number == ENOENT)
		return (ESCAPE_127);
	return (0);
}

void	exe_path_cmd(t_shell	*shell, t_token	*token)
{
	int		i;
	char	*full_cmd;

	i = -1;
	full_cmd = NULL;
	errno = 0;
	while (shell->path_var[++i])
	{
		full_cmd = ft_strjoin(shell->path_var[i], token->cmd);
		if (!access(full_cmd, X_OK))
			execve(full_cmd, token->args, shell->default_env);
		free(full_cmd);
	}
	if (!access(token->cmd, X_OK))
		execve(token->cmd, token->args, shell->default_env);
	exit(set_exit_status(token->cmd, errno));
}

void	exe_cmd_or_built(t_shell	*shell, t_token	*token)
{
	if (is_built_in(token->cmd))
		exe_built_in(token, shell);
	else
		exe_path_cmd(shell, token);
}
/*
void	execute_token(void *data, void *context)
{
	t_token	*token;
	t_shell	*shell;

	token = (t_token *)data;
	shell = (t_shell *)context;
	if (ft_samestr(token->line, PIPE_LINE))
		return ;
	if (is_built_in(token->cmd) && ft_tree_size(shell->token_tree) == 1)
		shell->exit_status = exe_built_in(data, context);
	shell->last_pid = fork();
	if (shell->last_pid < 0)
		perror("");
	if (shell->last_pid == 0)
	{
		if (is_built_in(token->cmd) && ft_tree_size(shell->token_tree) > 1)
			shell->exit_status = exe_built_in(data, context);
		else if (!is_built_in(token->cmd))
			shell->exit_status = exe_path_cmd(shell, token);
		exit(shell->exit_status);
	}
}
*/

void	wait_childs(t_token	*token, int	twice)
{
	if (twice)
		wait(&token->shell->exit_status);
	wait(&token->shell->exit_status);
	if (WIFEXITED(token->shell->exit_status))
		token->shell->exit_status = WEXITSTATUS(token->shell->exit_status);
	if (token->shell->child)
		exit(token->shell->exit_status);
}

void		exe_minishell_recursive(t_tree	*node)
{
	t_token	*token;
	int		pid;
	int		fd[2];

	if (!node)
		exit(EXIT_SUCCESS);
	token = (t_token *)node->data;
	pid = 0;
	if (ft_samestr(token->line, PIPE_LINE))
	{
		if (pipe(fd) == -1)
			return ;
		child_pipe_redir(node, token, pid, fd);
		wait_childs(token, TRUE);
	}
	else
		exe_comand_node(token, pid);
	return ;
}
