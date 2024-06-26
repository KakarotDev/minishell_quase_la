/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:01:22 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/26 20:23:01 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_next_token(t_dlist *t_next)
{
	int	type;

	type = t_next->tok->type;
	if (ft_is_redirect(type))
		return (SYNTAX_ERROR);
	return (EXIT_SUCCESS);
}

int	check_redirections(t_dlist **tokens)
{
	t_dlist		*c_tok;
	enum e_type	type;

	c_tok = *tokens;
	while (c_tok)
	{
		type = c_tok->tok->type;
		if (ft_is_redirect(type) && c_tok->next != NULL)
		{
			if (verify_next_token(c_tok->next))
				return (SYNTAX_ERROR);
		}
		else if (ft_is_redirect(type) && c_tok->next == NULL)
			return (SYNTAX_ERROR);
		if (c_tok->next == NULL)
			break ;
		c_tok = c_tok->next;
	}
	return (EXIT_SUCCESS);
}
