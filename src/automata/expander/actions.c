/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:09:12 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/01 20:37:10 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*get_next_var(t_automata	*a)
{
	char	*next_var;
	int		i;
	int		j;

	i = a->i + 1;
	j = 0;
	while (a->str[i] != '\0' && a->str[i] != ' ' && a->str[i] != '\t'
		&& a->str[i] != '\n' && a->str[i] != '$' && a->str[i] != '\''
		&& a->str[i] != '\"')
	{
		i++;
		j++;
	}
	next_var = ft_substr(a->str, a->i + 1, j);
	return (next_var);
}

void	insert_var(t_automata *a, void *data)
{
	t_token		*token;
	char		*str;
	char		*var;
	char		**pointer;

	token = (t_token *)data;
	pointer = (char **)token->data;
	var = get_next_var(a);
	str = find_value(token->shell->enviroment, var);
	free(var);
	*pointer = ft_strjoinfree(*pointer, str, 2);
}

void	insert_chr(t_automata *a, void *data)
{
	t_token		*token;
	char		str[2];
	char		**pointer;

	token = (t_token *)data;
	pointer = (char **)token->data;
	str[0] = a->str[a->i];
	str[1] = '\0';
	*pointer = ft_strjoinfree(*pointer, str, 0);
}
