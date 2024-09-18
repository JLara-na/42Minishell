/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:39 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/18 14:15:10 by jlara-na         ###   ########.fr       */
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
		perror("Built-in pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", buf);
	free(buf);
	return (EXIT_SUCCESS);
}
