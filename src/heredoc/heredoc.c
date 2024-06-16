/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:43:38 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/15 18:43:38 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	finish_heredoc(char **matrix, t_token *node, char *file, int *fds)
{
	its_in_heredoc(0);
	ft_free_matrix((void **) matrix);
	node->heredoc_file = file;
	close(fds[0]);
	close(fds[1]);
	return (0);
}

static char	**reviewing_delimiter(char *delimiter)
{
	t_dlist	*delimiter_node;
	char	**revised_delimiter;

	revised_delimiter = ft_calloc(3, sizeof(char *));
	revised_delimiter[1] = ft_itoa(0);
	if (!ft_strchr(delimiter, '\'') && !ft_strchr(delimiter, '\"'))
		*revised_delimiter[1] = '1';
	else
	{
		delimiter_node = ft_newnode_dlist(delimiter, WORD, NULL);
		send_for_quote_removal(delimiter_node);
		revised_delimiter[0] = ft_strdup(delimiter_node->tok->lex);
		free_struct_token(delimiter_node->tok);
		free(delimiter_node);
		return (revised_delimiter);
	}
	revised_delimiter[0] = ft_strdup(delimiter);
	return (revised_delimiter);
}

static char	*formatting_heredoc_file(void)
{
	char	*file_counter;
	char	*file;

	file_counter = ft_itoa(heredoc_file_counter(-1));
	file = ft_strjoin("/tmp/heredoc", file_counter);
	free(file_counter);
	return (file);
}

static void	write_to_heredoc_file(char *input, int fd, char bool_expansion)
{
	t_dlist	*temp;
	int		metadata[3];

	ft_memset(metadata, 0, sizeof(metadata));
	if (ft_have_char(input, '$') && bool_expansion == '1')
	{
		temp = ft_newnode_dlist(input, ASSIGNMENT_WORD, metadata);
		has_expansion(input, &temp->tok->metadata[0], &temp->tok->metadata[2]);
		while (temp->tok->type == ASSIGNMENT_WORD)
			send_for_expansion(temp);
		ft_putstr_fd(temp->tok->lex, fd);
		ft_putstr_fd("\n", fd);
		free_struct_token(temp->tok);
		free(temp);
	}
	else
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
	}
	return ;
}

void	heredoc(t_token *heredoc_tok, char *delimiter)
{
	char	*file;
	char	**revised_del;
	char	*input;
	int		fds[2];

	if (!delimiter)
		return ;
	file = formatting_heredoc_file();
	if (open_fds_heredoc(file, fds))
		return ;
	revised_del = reviewing_delimiter(delimiter);
	handle_signal_heredoc();
	while (TRUE)
	{
		its_in_heredoc(1);
		input = readline("> ");
		if (received_sigint(fds, input) || warning_heredoc(input, revised_del[0]))
			break ;
		if (!is_delimiter(delimiter, input))
			write_to_heredoc_file(input, fds[0], *revised_del[1]);
		else
			break ;
		free(input);
	}
	finish_heredoc(revised_del, heredoc_tok, file, fds);
}
