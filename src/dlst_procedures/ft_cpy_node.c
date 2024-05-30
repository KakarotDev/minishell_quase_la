/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:58:04 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 16:58:04 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_cpy_node(t_dlist *node)
{
	t_dlist	*new;

	if (!node)
		return (NULL);
	new = ft_newnode_dlist(node->tok->lex, node->tok->type,
			node->tok->metadata);
	return (new);
}
