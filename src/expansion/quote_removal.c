/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:33:59 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/15 22:45:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_content_of_squotes(char *lexeme, int pos, int fd)
{
	pos++;
	while (lexeme[pos] != '\'')
		pos += write(fd, &lexeme[pos], 1);
	pos++;
	return (pos);
}

static int	write_content_of_dquotes(char *lexeme, int pos, int fd)
{
	pos++;
	while (lexeme[pos] != '\"')
		pos += write(fd, &lexeme[pos], 1);
	pos++;
	return (pos);
}

static void	get_new_token(t_dlist *token, char *path)
{
	char	*new_lexeme;
	int		fd;

	fd = ft_open_fd(path, OPEN_RD);
	new_lexeme = get_next_line(fd);
	free(token->tok->lex);
	token->tok->lex = new_lexeme;
	close (fd);
	unlink(path);
	return ;
}

void	send_for_quote_removal(t_dlist *token)
{
	char	*lexeme;
	int		i;
	int		fd;

	fd = ft_open_fd("/tmp/.quote_removal", OPEN_WR);
	i = 0;
	lexeme = token->tok->lex;
	while (lexeme[i])
	{
		if (lexeme[i] == '\'')
			i = write_content_of_squotes(lexeme, i, fd);
		else if (lexeme[i] == '\"')
			i = write_content_of_dquotes(lexeme, i, fd);
		else
			i += write(fd, &lexeme[i], 1);
	}
	close(fd);
	get_new_token(token, "/tmp/.quote_removal");
}

void	quote_removal(t_dlist **tokens)
{
	t_dlist	*token;

	token = *tokens;
	while (token)
	{
		send_for_quote_removal(token);
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	return ;
}
