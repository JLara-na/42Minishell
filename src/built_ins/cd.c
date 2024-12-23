/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:24 by jlara-na          #+#    #+#             */
/*   Updated: 2024/12/23 17:35:48 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_env_pwd(t_shell	*shell, char	*old_pwd, char	*new_pwd)
{
	t_var	*oldpwd_var;
	t_var	*pwd_var;

	oldpwd_var = create_var(ft_strdup("OLDPWD"), ft_strdup(old_pwd));
	pwd_var = create_var(ft_strdup("PWD"), ft_strdup(new_pwd));
	add_new_var(shell->enviroment, oldpwd_var);
	add_new_var(shell->enviroment, pwd_var);
}

int	built_in_cd(t_shell	*shell, t_token	*token)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	if (ft_sarraysize(token->args) > 2)
		return (perror("Built-in cd arg error"), EXIT_FAILURE);
	oldpwd = getcwd(oldpwd, PATH_MAX);
	if (ft_sarraysize(token->args) == 1)
	{
		pwd = find_value(shell->enviroment, "HOME");
		if (chdir(pwd))
			return (free(oldpwd), perror("Built-in cd chdir()"), EXIT_FAILURE);
	}
	else
		if (chdir(token->args[1]))
			return (free(oldpwd), perror("Built-in cd chdir()"), EXIT_FAILURE);
	pwd = getcwd(pwd, PATH_MAX);
	update_env_pwd(shell, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
