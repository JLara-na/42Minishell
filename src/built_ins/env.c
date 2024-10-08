/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:33 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/12 11:16:09 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_list(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var->name && var->value)
		printf("%s=%s\n", var->name, var->value);
}

int	built_in_env(t_shell	*shell)
{
	ft_lstiter(shell->enviroment, print_list);
	return (EXIT_SUCCESS);
}
