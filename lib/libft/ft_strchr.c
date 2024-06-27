/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:38:52 by jlara-na          #+#    #+#             */
/*   Updated: 2022/06/20 19:56:40 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	j;
	char	*strg;

	i = 0;
	j = (char) c;
	strg = (char *) str;
	while (strg[i])
	{
		if (strg[i] == j)
			return (&strg[i]);
		i++;
	}
	if (strg[i] == j)
		return (&strg[i]);
	return (NULL);
}
