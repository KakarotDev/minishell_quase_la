/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:16:43 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/17 09:42:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct_token(t_token *tok)
{
	if (!tok)
		return ;
	free(tok->lex);
	free(tok->heredoc_file);
	free(tok);
	return ;
}
