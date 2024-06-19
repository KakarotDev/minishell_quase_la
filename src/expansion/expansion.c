/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:21:48 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/06 22:21:48 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	transcribing_content(char *content, int fd, long int *index, long int *start)
{
	*index = *start;
	if (*content == ' ')
	{
		content = ft_isspace(content, fd);
		*index = 0;
	}
	while (*content)
	{
		if (*content == ' ')
		{
			content = ft_isspace(content, fd);
			*index = 0;
		}
		content += write(fd, content, 1);
		*index += 1;
	}
	return ;
}

static void	write_with_quotes(t_dlist *token, char *content, char *varname)
{
	char	*lexeme;
	int		fd;

	fd = ft_open_fd("/tmp/.merge_token", OPEN_WR);
	lexeme = token->tok->lex;
	token->tok->metadata[0] = token->tok->metadata[1];
	while (token->tok->metadata[1]--)
		lexeme += write(fd, lexeme, 1);
	while (*content)
	{
		content += write(fd, content, 1);
		token->tok->metadata[0]++;
	}
	while (*varname == *(++lexeme) && *varname)
		varname++;
	while (*lexeme)
		lexeme += write(fd, lexeme, 1);
	close(fd);
	renewing_token(token);
	return ;
}

static void	write_without_quotes(t_dlist *token, char *content, char *varname)
{
	char	*lexeme;
	int		start;
	int		fd;

	fd = ft_open_fd("/tmp/.merge_token", OPEN_WR);
	lexeme = token->tok->lex;
	start = token->tok->metadata[1];
	while (start--)
		lexeme += write(fd, lexeme, 1);
	transcribing_content(content, fd,
		&token->tok->metadata[0], &token->tok->metadata[1]);
	while (*varname == *(++lexeme) && *varname
		&& (ft_isalnum(*lexeme) || *lexeme == '_' || *lexeme == '?'))
		varname++;
	while (*lexeme)
		lexeme += write(fd, lexeme, 1);
	close(fd);
	renewing_token(token);
	return ;
}

void	send_for_expansion(t_dlist *node)
{
	char	*varname;
	char	*variable;
	char	*content;

	varname = getting_varname(node->tok->lex, node->tok->metadata);
	if (!validating_varname(varname, &node->tok->metadata[2]))
	{
		if (!has_expansion(node->tok->lex,
				&node->tok->metadata[0], &node->tok->metadata[2]))
			return ;
	}
	variable = getting_variable(varname);
	if (ft_have_char(variable, '='))
		content = getting_content(variable);
	else
		content = ft_strdup(variable);
	if (node->tok->metadata[2])
		write_with_quotes(node, content, varname);
	else
		write_without_quotes(node, content, varname);
	free(varname);
	free(variable);
	free(content);
	return ;
}

// void	check_ambiguous_redirect(t_dlist *tok, t_dlist *next_tok)
// {
// 	if (!*tok->tok->lex)
// 	{
// 		tok->tok->metadata[3] = 1;
// 		tok->tok->metadata[0] = -1;
// 		return ;
// 	}
// 	if (tok->next != next_tok)
// 	{
// 		tok->tok->metadata[3] = 1;
// 		tok->tok->metadata[0] = -1;
// 		return ;
// 	}
// 	return ;
// }

void	expansion(t_dlist **tokens)
{
	t_dlist		*tok;

	tok = *tokens;
	while (tok)
	{
		if ((tok->tok->type == ASSIGNMENT_WORD || tok->tok->type == IO_FILE)
			&& tok->tok->metadata[0] > -1)
		{
			if (tok->tok->type == IO_FILE)
				tok->tok->metadata[3] = (long int) ft_strdup(tok->tok->lex);
			send_for_expansion(tok);
		}
		else if (tok->next == NULL)
			break ;
		else
			tok = tok->next;
	}
}
