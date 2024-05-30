/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_last_occur.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:38:07 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 16:38:32 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_dlist_last_occur(t_dlist **tokens, enum e_type type)
{
	t_dlist	*last_occur;
	t_dlist	*temp;

	temp = *tokens;
	last_occur = NULL;
	while (temp)
	{
		if (temp->tok->type == type)
			last_occur = temp;
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	if (last_occur)
		return (last_occur);
	return (NULL);
}
