/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:36:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/10 19:26:18 by jlara-na         ###   ########.fr       */
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

int	execute_built_in(t_shell	*shell, t_token	*token)
{
	if (ft_samestr(token->cmd, CD_BUILT))
		return (1);
	if (ft_samestr(token->cmd, ECHO_BUILT))
		return (1);
	if (ft_samestr(token->cmd, ENV_BUILT))
		return (built_in_env(shell), 1);
	if (ft_samestr(token->cmd, EXIT_BUILT))
		return (1);
	if (ft_samestr(token->cmd, EXPORT_BUILT))
		return (built_in_export(shell, token), 1);
	if (ft_samestr(token->cmd, PWD_BUILT))
		return (built_in_pwd(shell), 1);
	if (ft_samestr(token->cmd, UNSET_BUILT))
		return (1);
	return (0);
}

void	execute_path_cmd(t_shell	*shell, t_token	*token)
{
	int		i;
	char	*full_cmd;

	i = -1;
	full_cmd = NULL;
	while (shell->path_var[++i])
	{
		full_cmd = ft_strjoin(shell->path_var[i], token->cmd);
		if (!access(full_cmd, X_OK))
			execve(full_cmd, token->args, shell->default_env);
		free(full_cmd);
	}
	execve(token->cmd, token->args, shell->default_env);
	perror(token->cmd);
}

void	execute_token(void *data, void *context)
{
	t_token	*token;
	t_shell	*shell;
	pid_t	pid;
	int		status;

	token = (t_token *)data;
	shell = (t_shell *)context;
	if (ft_samestr(token->line, PIPE_LINE))
		return ;
	pid = fork();
	if (pid < 0)
		perror("");
	if (pid == 0)
	{
		if (is_built_in(token->cmd))
			execute_built_in(shell, token);
		else
			execute_path_cmd(shell, token);
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, &status, WEXITSTATUS(status));
}
