/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_single_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:21:16 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 10:21:16 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	skip_single_quotes(char *lexeme, long int *position)
{
	*position += 1;
	while (lexeme[*position] != '\'' && lexeme[*position])
		*position += 1;
	*position += 1;
	return ;
}
