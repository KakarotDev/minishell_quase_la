/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:33:33 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/29 22:33:33 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(int type, t_dlist **tokens)
{
	if (tokens)
		ft_destructor_struct(tokens);
	if (type == UNCLOSED_QUOTE)
		ft_putstr_fd("Error\n Syntax error an unclosed quoted\n", 2);
	else if (type == UNEXPECTED)
		ft_putstr_fd("Error\n Syntax error unexpected token\n", 2);
	return (SYNTAX_ERROR);
}
