/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:38 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 20:07:09 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_dlst_pop(t_dlist **tokens)
{
	t_dlist	*last;
	t_dlist	*new_last;

	if (!*tokens)
		return (NULL);
	last = ft_dlst_last(*tokens);
	new_last = last->prev;
	new_last->next = NULL;
	last->prev = NULL;
	return (last);
}
