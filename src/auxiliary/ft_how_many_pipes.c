/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_how_many_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:44:59 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/15 20:41:08 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	how_many_pipes(t_dlist *tokens)
// {
// 	int		i;
// 	t_dlist	*aux;

// 	i = 0;
// 	aux = tokens;
// 	while (aux->next)
// 		aux = aux->next;
// 	while (aux)
// 	{
// 		if (aux->tok->type == PIPE)
// 			i++;
// 		aux = aux->prev;
// 	}
// 	return (i);
// }

int	pipe_count(t_dlist *tokens)
{
	t_dlist	*aux;
	int		count;

	count = 0;
	aux = tokens;
	while (aux)
	{
		if (aux->tok->type == PIPE)
			count++;
		aux = aux->next;
	}
	return (count);
}
