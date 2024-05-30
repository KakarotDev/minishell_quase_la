/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:56:01 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 10:56:01 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_validation(char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = FALSE;
	d_quote = FALSE;
	while (*input)
	{
		if (*input == '\'' && !s_quote && !d_quote)
			s_quote = TRUE;
		else if (*input == '\'' && s_quote)
			s_quote = FALSE;
		if (*input == '\"' && !d_quote && !s_quote)
			d_quote = TRUE;
		else if (*input == '\"' && d_quote)
			d_quote = FALSE;
		input++;
	}
	if (s_quote || d_quote)
		return (TRUE);
	return (FALSE);
}
