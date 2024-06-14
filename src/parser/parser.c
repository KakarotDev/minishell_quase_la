/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:55:41 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/14 20:23:48 by parthur-         ###   ########.fr       */
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
	if (parser_validation(tokens) == 2)
	{
		last_exit_status(2);
		return ;
	}
	ast_function(tokens);
	return ;
}
