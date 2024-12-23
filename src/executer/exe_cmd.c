/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:18:47 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/23 18:42:33 by jlara-na         ###   ########.fr       */
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
	return (0);
}

void	exe_path_cmd(t_shell	*shell, t_token	*token)
{
	int		i;
	char	*full_cmd;
	char	*path_var;

	i = -1;
	full_cmd = NULL;
	errno = 0;
	path_var = find_value(shell->enviroment, "PATH");
	if (!ft_strchr(token->cmd, '/') && path_var)
	{
		free(path_var);
		while (shell->path_var[++i])
		{
			full_cmd = ft_strjoin(shell->path_var[i], token->cmd);
			if (!access(full_cmd, X_OK))
				execve(full_cmd, token->args, shell->default_env);
			free(full_cmd);
		}
	}
	free(path_var);
	if (!access(token->cmd, X_OK))
		execve(token->cmd, token->args, shell->default_env);
	exit(set_exit_status(token->cmd, errno));
}
