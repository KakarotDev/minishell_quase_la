/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:44:53 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/26 20:22:20 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_and_prev_pipes(int t_prev, int t_next)
{
	if (t_prev == PIPE || ft_is_redirect(t_prev))
		return (SYNTAX_ERROR);
	if (t_next == PIPE)
		return (SYNTAX_ERROR);
	return (EXIT_SUCCESS);
}

int	check_pipes(t_dlist **tokens)
{
	t_dlist	*c_tok;

	c_tok = *tokens;
	while (c_tok)
	{
		if (c_tok->tok->type == PIPE && c_tok->next != NULL
			&& c_tok->prev != NULL)
		{
			if (check_next_and_prev_pipes(c_tok->prev->tok->type,
					c_tok->next->tok->type))
				return (SYNTAX_ERROR);
		}
		else if ((c_tok->next == NULL || c_tok->prev == NULL)
			&& c_tok->tok->type == PIPE)
			return (SYNTAX_ERROR);
		if (c_tok->next == NULL)
			break ;
		c_tok = c_tok->next;
	}
	return (EXIT_SUCCESS);
}
