/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_have_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:39:34 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/02 16:39:42 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dlist_have_type(t_dlist **tokens, enum e_type type)
{
	t_dlist	*temp;

	if (!tokens)
		return (-1);
	if (!*tokens)
		return (-1);
	temp = ft_dlst_last(*tokens);
	while (temp)
	{
		if (temp->tok->type == type)
			return (1);
		if (temp->prev == NULL)
			break ;
		temp = temp->prev;
	}
	return (0);
}
