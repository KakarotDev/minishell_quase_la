/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:00:26 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/09 11:00:26 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_dlst_last(t_dlist *node)
{
	t_dlist	*temp;

	if (!node)
		return (NULL);
	temp = node;
	while (temp->next)
	{
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	return (temp);
}
