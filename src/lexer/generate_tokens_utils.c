/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:29:17 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/25 21:41:20 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isexpansion(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') \
	|| (c >= 'a' && c <= 'z') || c == '_' || c == '?')
		return (1);
	return (0);
}

int	has_expansion(char *lex, long int *index, long int *is_quoted)
{
	while (lex[*index])
	{
		if (lex[*index] == '$' && (ft_isexpansion(lex[*index + 1])))
			break ;
		if (lex[*index] == '\"' && !(*is_quoted))
			*is_quoted = TRUE;
		else if (lex[*index] == '\"' && *is_quoted)
			*is_quoted = FALSE;
		if (lex[*index] == '\'' && !(*is_quoted))
			skip_single_quotes(lex, index);
		else
			*index += 1;
	}
	if (lex[*index] == '$' && !(*is_quoted && lex[((*index) + 1)] == '\"'))
		return (TRUE);
	*index = -1;
	return (FALSE);
}
