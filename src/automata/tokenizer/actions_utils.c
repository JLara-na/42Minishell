/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 20:36:19 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/19 19:50:48 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	quote_len(char	*str, char type)
{
	int	i;

	i = 1;
	while (str[i] != type && str[i] != '\0')
		i++;
	return (i);
}

int	arg_length(char	*arg)
{
	int	len;

	len = 0;
	while (arg[len] == ' ' || arg[len] == '\t')
		len++;
	while (arg[len] != '\0' && arg[len] != '<' && arg[len] != '>')
	{
		if (arg[len] == '\'' || arg[len] == '\"')
			len += quote_len(arg + len, arg[len]);
		if ((arg[len] == ' ' || arg[len] == '\t'
				|| arg[len] == '\n'))
			break ;
		len++;
	}
	return (len);
}

char	*get_next_word(t_automata	*a)
{
	char	*substr;
	char	*trim;
	int		i;

	i = 0;
	i = arg_length(a->str + a->i);
	substr = NULL;
	trim = NULL;
	substr = ft_substr(a->str, a->i, i);
	trim = ft_strtrim(substr, " \t\n");
	free(substr);
	a->j = a->i;
	return (trim);
}
