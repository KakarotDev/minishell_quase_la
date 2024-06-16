/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:22 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/15 22:55:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_next_token(t_dlist *t_next)
{
	int	type;

	type = t_next->tok->type;
	if (ft_is_redirect(type))
		return (2);
	return (0);
}

int	check_redirections(t_dlist **tokens)
{
	t_dlist		*c_tok;
	enum e_type	type;

	if (!tokens)
		return (0);
	if (!*tokens)
		return (0);
	c_tok = *tokens;
	while (c_tok)
	{
		type = c_tok->tok->type;
		if (ft_is_redirect(type) && c_tok->next != NULL)
		{
			if (verify_next_token(c_tok->next))
				return (2);
		}
		else if (ft_is_redirect(type) && c_tok->next == NULL)
			return (2);
		if (c_tok->next == NULL)
			break ;
		c_tok = c_tok->next;
	}
	return (EXIT_SUCCESS);
}
