/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:39 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/11 20:09:50 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	built_in_pwd(t_shell	*shell)
{
	char	*buf;

	(void)shell;
	buf = NULL;
	buf = getcwd(buf, PATH_MAX);
	if (!buf)
	{
		buf = find_value(shell->enviroment, "PWD");
		if (buf)
		{
			printf("%s\n", buf);
			free(buf);
			return (EXIT_SUCCESS);
		}
		perror("Built-in pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", buf);
	free(buf);
	return (EXIT_SUCCESS);
}
