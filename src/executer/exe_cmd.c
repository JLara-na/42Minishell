/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:18:47 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/17 17:42:55 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_exit_status(char	*cmd, int error_number)
{
	perror(cmd);
	if (error_number == EACCES)
		return (ESCAPE_126);
	if (error_number == ENOENT)
		return (ESCAPE_127);
	if (g_signal_data == SIGINT)
		return (ESCAPE_130);
	return (0);
}

void	execute_multiple_paths(t_shell *shell, t_token *token, char **paths)
{
	char	*full_cmd;
	int		i;

	i = -1;
	full_cmd = NULL;
	while (paths[++i])
	{
		full_cmd = ft_strjoin(paths[i], token->cmd);
		if (!access(full_cmd, X_OK))
			execve(full_cmd, token->args, shell->default_env);
		free(full_cmd);
	}
}

void	exe_path_cmd(t_shell *shell, t_token *token)
{
	char	*path_var;
	char	**paths;

	errno = 0;
	path_var = find_value(shell->enviroment, "PATH");
	paths = get_path_var(shell);
	update_default_env(shell);
	if (!ft_strchr(token->cmd, '/') && path_var)
	{
		free(path_var);
		execute_multiple_paths(shell, token, paths);
	}
	else
	{
		if (!access(token->cmd, X_OK))
			execve(token->cmd, token->args, shell->default_env);
		free(path_var);
	}
	ft_free_sarray(paths);
	ft_free_sarray(shell->default_env);
	exit(set_exit_status(token->cmd, errno));
}
