/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:06:10 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 19:07:19 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
