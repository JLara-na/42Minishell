/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_in_order.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:53:20 by jlara-na          #+#    #+#             */
/*   Updated: 2024/07/01 21:19:42 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_in_order(t_tree *node, void (*ft)(void*))
{
	if (node != NULL)
	{
		ft_tree_in_order(node->left, ft);
		ft(node->data);
		ft_tree_in_order(node->right, ft);
	}
}