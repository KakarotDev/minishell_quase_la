/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newnode_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:00:18 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/09 11:00:18 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_newnode_dlist(char *lexeme, enum e_type type, int expansion_data[])
{
	t_dlist	*new_node;

	new_node = (t_dlist *) ft_calloc(1, sizeof(t_dlist));
	new_node->tok = (t_token *) ft_calloc(1, sizeof(t_token));
	new_node->tok->lex = ft_strdup(lexeme);
	new_node->tok->type = type;
	new_node->tok->heredoc_file = NULL;
	ft_cpy_array_data(new_node->tok->metadata, expansion_data, 4);
	return (new_node);
}
