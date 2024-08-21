/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:56:46 by jlara-na          #+#    #+#             */
/*   Updated: 2024/08/21 23:09:24 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bool	find_var(void *content, void *context)
{
	t_var	*var;
	char	*name;
	size_t	lena;
	size_t	lenb;

	var = (t_var *)content;
	name = (char *)context;
	lena = ft_strlen(var->name);
	lenb = ft_strlen(name);
	if (lena < lenb)
		lena = lenb;
	if (!ft_strncmp(var->name, name, lena))
		return (TRUE);
	return (FALSE);
}

char	*find_value(t_list	*env, char	*name)
{
	t_list	*node;
	t_var	*var;
	char	*value;

	value = NULL;
	node = ft_lstfind(env, find_var, name);
	if (node)
	{
		var = (t_var *)(node->content);
		value = ft_strdup(var->value);
	}
	return (value);
}
