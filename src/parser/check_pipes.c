/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:44:53 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 10:49:35 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_and_prev_pipes(int t_prev, int t_next)
{
	if (t_prev == PIPE || ft_is_redirect(t_prev))
		return (2);
	if (t_next == PIPE)
		return (2);
	return (0);
}

int	check_pipes(t_dlist **tokens)
{
	t_dlist	*c_tok;

	if (!tokens)
		return (0);
	if (!*tokens)
		return (0);
	c_tok = *tokens;
	while (c_tok)
	{
		if (c_tok->tok->type == PIPE && c_tok->next != NULL
			&& c_tok->prev != NULL)
		{
			if (check_next_and_prev_pipes(c_tok->prev->tok->type,
					c_tok->next->tok->type))
				return (2);
		}
		else if ((c_tok->next == NULL || c_tok->prev == NULL)
			&& c_tok->tok->type == PIPE)
			return (2);
		if (c_tok->next == NULL)
			break ;
		c_tok = c_tok->next;
	}
	return (0);
}
