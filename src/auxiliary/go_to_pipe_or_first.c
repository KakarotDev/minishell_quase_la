/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_pipe_or_first.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:19:47 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/29 23:30:31 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*go_to_pipe_or_first(t_dlist *aux_t)
{
	while (aux_t->next != NULL)
			aux_t = aux_t->next;
	while (aux_t->tok->type != PIPE && aux_t->prev != NULL)
		aux_t = aux_t->prev;
	return (aux_t);
}
