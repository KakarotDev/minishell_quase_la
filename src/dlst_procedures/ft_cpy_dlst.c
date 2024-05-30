/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_dlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:38:58 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 17:34:44 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	**ft_cpy_dlst(t_dlist *start_point)
{
	t_dlist	**new_dlist;
	t_dlist	*temp;
	t_dlist	*start;

	new_dlist = (t_dlist **) ft_calloc(1, sizeof(t_dlist **));
	*new_dlist = ft_cpy_node(start_point);
	start = *new_dlist;
	temp = start_point;
	while (temp)
	{
		if (temp->next == NULL)
			break ;
		temp = temp->next;
		start->next = ft_cpy_node(temp);
		start = start->next;
	}
	return (new_dlist);
}
