/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:28:50 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/30 02:28:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	there_is_an_expansion_in_this_word(char *lexeme, t_dlist **head)
{
	long int	metadata[4];

	ft_memset(metadata, 0, sizeof(metadata));
	if (ft_have_char(lexeme, '$'))
	{
		if (has_expansion(lexeme, &metadata[0], &metadata[2]))
		{
			ft_append_dlist(head, ft_newnode_dlist(lexeme, 7, metadata));
			return (TRUE);
		}
		ft_append_dlist(head, ft_newnode_dlist(lexeme, 6, metadata));
		return (TRUE);
	}
	else
	{
		ft_append_dlist(head, ft_newnode_dlist(lexeme, 6, metadata));
		return (TRUE);
	}
	return (FALSE);
}

static int	ft_isword(t_dlist **head, char *lexeme)
{
	t_dlist		*last_tok;
	long int	met_d[4];

	last_tok = ft_dlst_last(*head);
	ft_memset(met_d, 0, sizeof(met_d));
	if (last_tok != NULL)
	{
		if (last_tok->tok->type == H_DOC || last_tok->tok->type == APPEND
			|| last_tok->tok->type == R_OUT || last_tok->tok->type == R_IN)
		{
			if (last_tok->tok->type == H_DOC)
			{
				ft_append_dlist(head, ft_newnode_dlist(lexeme, H_DEL, met_d));
				heredoc(last_tok->tok, last_tok->next->tok->lex);
				handle_signal();
			}
			else
			{
				has_expansion(lexeme, &met_d[0], &met_d[2]);
				ft_append_dlist(head, ft_newnode_dlist(lexeme, IO_FILE, met_d));
			}
			return (TRUE);
		}
	}
	return (there_is_an_expansion_in_this_word(lexeme, head));
}

static int	ft_isop(t_dlist **head, char **lexemes, int *i)
{
	long int	data[4];
	int			start;

	start = *i;
	ft_memset(data, 0, sizeof(data));
	if (!ft_strncmp(lexemes[*i], "<<", 2))
		ft_append_dlist(head, ft_newnode_dlist(lexemes[*i], H_DOC, data));
	else if (!ft_strncmp(lexemes[*i], ">>", 2))
		ft_append_dlist(head, ft_newnode_dlist(lexemes[*i], APPEND, data));
	else if (!ft_strncmp(lexemes[*i], "|", 1))
		handling_pipe(head, lexemes, i);
	else if (!ft_strncmp(lexemes[*i], ">", 1))
		ft_append_dlist(head, ft_newnode_dlist(lexemes[*i], R_OUT, data));
	else if (!ft_strncmp(lexemes[*i], "<", 1))
		ft_append_dlist(head, ft_newnode_dlist(lexemes[*i], R_IN, data));
	else
		return (FALSE);
	return (TRUE);
}

char	**get_all_lexemes(char *file)
{
	int				fd;
	char			*line;
	char			*all_content;
	char			*temp;
	char			**all_lexemes;

	fd = ft_open_fd(file, OPEN_RD);
	line = get_next_line(fd);
	all_content = ft_strdup(NULL);
	while (line != NULL)
	{
		temp = all_content;
		all_content = ft_strjoin(all_content, line);
		free(line);
		if (temp)
			free(temp);
		line = get_next_line(fd);
	}
	all_lexemes = ft_split(all_content, '\n');
	free(all_content);
	close(fd);
	unlink(file);
	return (all_lexemes);
}

t_dlist	**generate_tokens(char *file)
{
	t_dlist	**dlist_tokens;
	char	**lexemes;
	int		i;
	int		j;

	heredoc_file_counter(0);
	dlist_tokens = (t_dlist **) ft_calloc(1, sizeof(t_dlist **));
	lexemes = get_all_lexemes(file);
	if (lexemes == NULL)
		return (NULL);
	i = 0;
	j = i;
	while (lexemes[i])
	{
		if (ft_isop(dlist_tokens, lexemes, &i))
			j++;
		else if (ft_isword(dlist_tokens, lexemes[i]))
			j++;
		if (j > i)
			i = j;
		else if (lexemes[i])
			i++;
	}
	ft_free_matrix((void **) lexemes);
	return (dlist_tokens);
}
