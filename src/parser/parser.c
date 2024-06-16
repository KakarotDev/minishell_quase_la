/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:55:41 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 01:31:15 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_dlist **tokens)
{
	if (!tokens || !*tokens)
	{
		if (!*tokens)
			ft_destructor_struct(tokens);
		return ;
	}
	if (received_sigint_in_heredoc(-1))
	{
		ft_destructor_struct(tokens);
		return ;
	}
	if (parser_validation(tokens) == SYNTAX_ERROR)
	{
		last_exit_status(SYNTAX_ERROR);
		return ;
	}
	ast_function(tokens);
	return ;
}
