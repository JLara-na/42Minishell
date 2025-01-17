/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:24 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/16 02:03:14 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_vars(t_shell *shell, t_var *pwd, t_var *oldpwd)
{
	if (!shell->enviroment)
		ft_lstadd_back(&shell->enviroment,
			ft_lstnew(create_var(ft_strdup("PWD"), ft_strdup("./"))));
	add_new_var(shell, oldpwd);
	add_new_var(shell, pwd);
}

t_var	*auxiliar_function(t_shell *shell, char *old_pwd)
{
	char	*aux;

	if (!old_pwd)
	{
		aux = find_value(shell->enviroment, "PWD");
		return (create_var(ft_strdup("OLDPWD"), aux));
	}
	else
		return (create_var(ft_strdup("OLDPWD"), ft_strdup(old_pwd)));
}

void	update_env_pwd(t_shell *shell, t_token *token,
		char *old_pwd, char *new_pwd)
{
	t_var	*oldpwd_var;
	t_var	*pwd_var;
	char	*aux;
	int		i;

	i = 0;
	oldpwd_var = auxiliar_function(shell, old_pwd);
	if (!new_pwd)
	{
		aux = find_value(shell->enviroment, "PWD");
		if (aux)
		{
			new_pwd = ft_strjoinfree(aux, "/", 0);
			new_pwd = ft_strjoinfree(new_pwd, token->args[1], 0);
			i = 1;
		}
	}
	if (new_pwd)
		pwd_var = create_var(ft_strdup("PWD"), ft_strdup(new_pwd));
	else
		pwd_var = create_var(ft_strdup("PWD"), ft_strdup(""));
	if (i == 1)
		free (new_pwd);
	add_vars(shell, pwd_var, oldpwd_var);
}

int	built_in_cd(t_shell	*shell, t_token	*token)
{
	char	*oldpwd;
	char	*pwd;
	char	*aux;

	if (ft_sarraysize(token->args) > 2)
		return (perror("Built-in cd arg error"), EXIT_FAILURE);
	oldpwd = getcwd(oldpwd, PATH_MAX);
	if (ft_sarraysize(token->args) == 1)
	{
		aux = find_value(shell->enviroment, "HOME");
		if (chdir(aux))
			return (free(aux), free(oldpwd),
				perror("Built-in cd chdir()"), EXIT_FAILURE);
		free(aux);
	}
	else
		if (chdir(token->args[1]) != 0)
			return (free(oldpwd), perror("Built-in cd chdir()"), EXIT_FAILURE);
	pwd = getcwd(pwd, PATH_MAX);
	update_env_pwd(shell, token, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
