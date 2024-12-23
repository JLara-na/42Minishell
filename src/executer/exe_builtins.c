/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:02:47 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/23 02:28:02 by jlara-na         ###   ########.fr       */
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
		return (shell->exit_status = built_in_cd(shell, token));
	if (ft_samestr(token->cmd, ECHO_BUILT))
		return (shell->exit_status = built_in_echo(token));
	if (ft_samestr(token->cmd, ENV_BUILT))
		return (shell->exit_status = built_in_env(shell));
	if (ft_samestr(token->cmd, EXIT_BUILT))
		return (shell->exit_status = built_in_exit(shell));
	if (ft_samestr(token->cmd, EXPORT_BUILT))
		return (shell->exit_status = built_in_export(shell, token));
	if (ft_samestr(token->cmd, PWD_BUILT))
		return (shell->exit_status = built_in_pwd(shell));
	if (ft_samestr(token->cmd, UNSET_BUILT))
		return (shell->exit_status = built_in_unset(shell, token));
	return (1);
}
