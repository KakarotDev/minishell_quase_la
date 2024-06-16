/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:49:14 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:09:26 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_tokens(t_dlist **exec_tokens)
{
	t_dlist	*temp;
	int		i;

	i = 0;
	if (!exec_tokens)
		return (i);
	if (!*exec_tokens)
		return (i);
	temp = *exec_tokens;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
