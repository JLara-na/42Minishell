/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:36:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/26 22:02:12 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_token(void *data, void *context)
{
	t_token	*token;
	t_shell	*shell;


	token = (t_token *)data;
	shell = (t_shell *)context;
	if (token->cmd && ft_samestr(token->cmd, "export"))
		built_in_export(shell, token);
	if (token->cmd && ft_samestr(token->cmd, "env") && !token->args[1])
		built_in_env(shell);
}
