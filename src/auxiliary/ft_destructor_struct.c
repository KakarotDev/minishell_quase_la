/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destructor_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:36:46 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/23 16:45:40 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_destructor_struct(t_dlist **struct_to_clean)
{
	t_dlist	*temp;
	t_dlist	*temp1;

	if (!*struct_to_clean)
	{
		free(struct_to_clean);
		struct_to_clean = NULL;
		return ;
	}
	temp = *struct_to_clean;
	while (temp)
	{
		temp1 = temp;
		temp = temp->next;
		free_struct_token(temp1->tok);
		free(temp1);
	}
	free(struct_to_clean);
	struct_to_clean = NULL;
	return ;
}
