/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_dlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:00:34 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/09 11:00:34 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_dlist(t_dlist **head, t_dlist *node)
{
	t_dlist	*temp;

	if (!head)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	temp = ft_dlst_last(*head);
	temp->next = node;
	node->prev = temp;
	return ;
}
