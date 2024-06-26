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

int	quote_validation(char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !s_quote && !d_quote)
			s_quote = 1;
		else if (*input == '\'' && s_quote)
			s_quote = 0;
		if (*input == '\"' && !d_quote && !s_quote)
			d_quote = 1;
		else if (*input == '\"' && d_quote)
			d_quote = 0;
		input++;
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
}
