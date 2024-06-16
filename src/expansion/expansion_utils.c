/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:11:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 11:11:55 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getting_variable(char *varname)
{
	if (ft_isdigit(*varname))
		return (ft_strdup(""));
	if (!ft_strncmp(varname, "?", 1))
		return (ft_itoa(last_exit_status(-1)));
	return (read_var(hook_environ(NULL, 0), varname));
}

char	*getting_varname(char *lexeme, int expansion_metadata[])
{
	expansion_metadata[1] = expansion_metadata[0]++;
	if (!ft_isalpha(lexeme[expansion_metadata[0]])
		&& lexeme[expansion_metadata[0]] != '_')
		return (ft_strndup(lexeme, expansion_metadata[1] + 1,
				expansion_metadata[0] - expansion_metadata[1]));
	while ((ft_isalnum(lexeme[expansion_metadata[0]])
			|| lexeme[expansion_metadata[0]] == '_')
		&& lexeme[expansion_metadata[0]])
		expansion_metadata[0]++;
	return (ft_strndup(lexeme, expansion_metadata[1] + 1,
			expansion_metadata[0] - (expansion_metadata[1] + 1)));
}

char	*getting_content(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (ft_strdup(""));
	while (var[i] && var[i] != '=')
		i++;
	if (i == 0)
		return (ft_strdup(""));
	i++;
	return (ft_strndup(var, i, ft_strlen(var) - i));
}

void	renewing_token(t_dlist *tok)
{
	t_dlist	*new;
	char	**lexs;
	int		i;

	i = 0;
	new = tok;
	lexs = get_all_lexemes("/tmp/.merge_token");
	while (lexs[i])
	{
		if (!lexs[i + 1])
			new = dealing_with_last_lexeme(lexs[i], new, tok, i);
		else if (tok->tok->type == IO_FILE)
			new = ft_add_next(new,
					ft_newnode_dlist(lexs[i], IO_FILE, tok->tok->metadata), i);
		else if (tok->tok->type == ASSIGNMENT_WORD)
			new = ft_add_next(new,
					ft_newnode_dlist(lexs[i], WORD, tok->tok->metadata), i);
		i++;
	}
	if (!lexs[i] && i == 0)
		new = ft_add_next(new, ft_newnode_dlist(NULL, WORD, NULL), i);
	ft_free_matrix((void **) lexs);
	return ;
}

t_dlist	*dealing_with_last_lexeme(char *lex, t_dlist *new, t_dlist *tok, int i)
{
	int	expansion_bool;

	expansion_bool = has_expansion(lex,
			&tok->tok->metadata[0], &tok->tok->metadata[2]);
	if (expansion_bool && tok->tok->type == IO_FILE)
		new = ft_add_next(new,
				ft_newnode_dlist(lex, IO_FILE, tok->tok->metadata), i);
	else if (tok->tok->type == IO_FILE)
		new = ft_add_next(new,
				ft_newnode_dlist(lex, IO_FILE, tok->tok->metadata), i);
	else if (expansion_bool && tok->tok->type == ASSIGNMENT_WORD)
		new = ft_add_next(new,
				ft_newnode_dlist(lex, ASSIGNMENT_WORD, tok->tok->metadata), i);
	else if (tok->tok->type == ASSIGNMENT_WORD)
		new = ft_add_next(new,
				ft_newnode_dlist(lex, WORD, tok->tok->metadata), i);
	return (new);
}
