/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 20:36:19 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/04 22:27:19 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
/*
int	arg_length(char	*arg)
{
	int	len;

	len = 0;
	if (arg[0] == '\"' || arg[0] == '\'')
	{
		len++;
		while (arg[len] != arg[0])
			len++;
		len++;
	}
	else
		while ((arg[len] != ' ' && arg[len] != '\t' && arg[len] != '\n'
				&& arg[0]) && arg[len] != '\0')
			len++;
	return (len);
}

char	*get_next_word(t_automata	*a)
{
	char	*substr;
	char	*trm;
	int		i;

	i = 0;
    while (a->str[a->i + i] == ' ' || a->str[a->i + i] == '\t' || a->str[a->i + i] == '\n' || a->str[a->i + i] == '\0')
    {
        i++;
    }
    while (a->str[a->i + i] != ' ' && a->str[a->i + i] != '\t'
		&& a->str[a->i + i] != '\n' && a->str[a->i + i] != '\0'
		&& a->str[a->i + i] != '<' && a->str[a->i + i] != '>'
		&& a->str[a->i + i] != '|')
		i++;
	substr = ft_substr(a->str, a->i, i);
	a->j = a->i;
	trm = ft_strtrim(substr, " ");
	free(substr);
	return (trm);
}
*/
int	arg_length(char	*arg)
{
	int	len;

	len = 0;
	if (arg[0] == '\"' || arg[0] == '\'')
	{
		len++;
		while (arg[len] != arg[0])
			len++;
		len++;
	}
	else
		while ((arg[len] != ' ' && arg[len] != '\t' && arg[len] != '\n'
				&& arg[0]) && arg[len] != '\0')
			len++;
	return (len);
}

char	*get_next_word(t_automata	*a)
{
	char	*substr;
	char	*trm;
	char	*next_word;
	int		i;

	i = 0;
	while (a->str[a->i + i] != '<' && a->str[a->i + i] != '>'
		&& a->str[a->i + i] != '\0')
		i++;
	substr = ft_substr(a->str, a->i, i);
	a->j = a->i;
	trm = ft_strtrim(substr, " ");
	free(substr);
	i = arg_length(trm);
	next_word = ft_substr(trm, 0, i);
	free(trm);
	return (next_word);
}