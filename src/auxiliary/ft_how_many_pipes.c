/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_how_many_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:44:59 by parthur-          #+#    #+#             */
/*   Updated: 2024/05/09 18:38:39 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_pipes(t_dlist *tokens)
{
	int		i;
	t_dlist	*aux;

	i = 0;
	aux = tokens;
	while (aux->next)
		aux = aux->next;
	while (aux)
	{
		if (aux->tok->type == PIPE)
			i++;
		aux = aux->prev;
	}
	return (i);
}

int	have_pipe(t_dlist *tokens)
{
	t_dlist	*aux;

	aux = tokens;
	while (aux)
	{
		if (aux->tok->type == PIPE)
			return (how_many_pipes(tokens));
		aux = aux->next;
	}
	return (0);
}
