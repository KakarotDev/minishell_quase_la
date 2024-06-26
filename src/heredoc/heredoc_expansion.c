/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:39:45 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 20:14:50 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dlist	*dealing_with_last_lexeme_heredoc(char *lex, t_dlist *new,
		t_dlist *tok, int i)
{
	int	expansion_bool;

	expansion_bool = has_expansion_heredoc(lex,
			&tok->tok->metadata[0]);
	if (expansion_bool && tok->tok->type == ASSIGNMENT_WORD)
		new = ft_add_next(new,
				ft_newnode_dlist(lex, ASSIGNMENT_WORD, tok->tok->metadata), i);
	else if (tok->tok->type == ASSIGNMENT_WORD)
		new = ft_add_next(new,
				ft_newnode_dlist(lex, WORD, tok->tok->metadata), i);
	return (new);
}

void	renewing_heredoc_token(t_dlist *tok)
{
	t_dlist		*new;
	char		**lexs;
	int			i;

	i = 0;
	new = tok;
	lexs = get_all_lexemes("/tmp/.merge_token");
	while (lexs[i])
	{
		if (!lexs[i + 1])
			new = dealing_with_last_lexeme_heredoc(lexs[i], new, tok, i);
		else if (tok->tok->type == ASSIGNMENT_WORD)
			new = ft_add_next(new,
					ft_newnode_dlist(lexs[i], WORD, tok->tok->metadata), i);
		i++;
	}
	if (!lexs[i] && i == 0)
		new = ft_add_next(new,
				ft_newnode_dlist(NULL, WORD, tok->tok->metadata), i);
	ft_free_matrix((void **) lexs);
	return ;
}

void	send_for_expansion_heredoc(t_dlist *node)
{
	char	*varname;
	char	*variable;
	char	*content;

	varname = getting_varname(node->tok->lex, node->tok->metadata);
	variable = getting_variable(varname);
	if (ft_have_char(variable, '='))
		content = getting_content(variable);
	else
		content = ft_strdup(variable);
	write_with_quotes(node, content, varname, 1);
	free(varname);
	free(variable);
	free(content);
	return ;
}

int	has_expansion_heredoc(char *lex, long int *index)
{
	while (lex[*index])
	{
		if (lex[*index] == '$' && (ft_isexpansion(lex[*index + 1])))
			break ;
		*index += 1;
	}
	if (lex[*index] == '$' && (lex[(*index) + 1] != '\''
			|| lex[(*index) + 1] != '\"'))
		return (TRUE);
	*index = -1;
	return (FALSE);
}
