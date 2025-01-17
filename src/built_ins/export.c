/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:37 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/16 02:08:33 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_new_var(t_shell	*shell, t_var	*newvar)
{
	t_list	*node;
	t_var	*var;

	node = NULL;
	var = NULL;
	if (shell->enviroment)
	{
		node = ft_lstfind(shell->enviroment, find_var, newvar->name);
		if (node)
		{
			var = (t_var *)(node->content);
			free(var->value);
			var->value = newvar->value;
			free(newvar->name);
			free(newvar);
			newvar = NULL;
		}
		else
		{
			node = shell->enviroment;
			ft_lstadd_back(&node, ft_lstnew(newvar));
		}
	}
	if (!shell->enviroment)
		ft_lstadd_back(&shell->enviroment, ft_lstnew(newvar));
}

int	is_valid_var_name(char	*arg)
{
	if (!arg)
		return (0);
	if (ft_chrpos(arg, '=') == -1 || (!ft_isalpha(*arg) && *arg != '_'))
		return (0);
	while (*arg && *arg != '=')
	{
		if (*arg != '_' && !ft_isalnum(*arg))
			return (0);
		arg++;
	}
	return (1);
}

void	print_export(void	*content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var->name && var->value)
		printf("declare -x %s=%s\n", var->name, var->value);
}

void	set_vars(t_shell *shell, int *return_val, int *i, int *j)
{
	(void)shell;
	*return_val = EXIT_SUCCESS;
	*i = 0;
	*j = 0;
}

int	built_in_export(t_shell *shell, t_token	*token)
{
	t_var	*newvar;
	char	*value;
	int		i;
	int		j;
	int		return_val;

	set_vars(shell, &return_val, &i, &j);
	if (!token->args[1])
		ft_lstiter(shell->enviroment, print_export);
	while (token->args[++i])
	{
		if (is_valid_var_name(token->args[i]))
		{
			j = ft_chrpos(token->args[i], '=');
			if (j != -1)
				value = ft_substr(token->args[i], j + 1, INT_MAX);
			else
				value = ft_calloc(sizeof(char *), 1);
			newvar = create_var(ft_substr(token->args[i], 0, j), value);
			add_new_var(shell, newvar);
		}
		else
			return_val = EXIT_FAILURE;
	}
	return (return_val);
}
