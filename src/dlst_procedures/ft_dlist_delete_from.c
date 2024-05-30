/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_delete_from.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:33:57 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 17:36:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dlist_delete_from(t_dlist *start_node)
{
	t_dlist	*temp;
	t_dlist	*prev;

	if (!start_node)
		return ;
	if (start_node->prev)
	{
		prev = start_node->prev;
		prev->next = NULL;
	}
	while (start_node)
	{
		temp = start_node;
		start_node = temp->next;
		free_struct_token(temp->tok);
		free(temp);
	}
	return ;
}
