/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:40:19 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/25 21:40:19 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_heredoc(t_dlist **head, char **lexemes, int *i)
{
	t_dlist		*node;
	long int	metadata[4];

	ft_memset(metadata, 0, sizeof(metadata));
	node = ft_newnode_dlist(lexemes[*i], H_DOC, metadata);
	ft_append_dlist(head, node);
	ft_add_next(node, ft_newnode_dlist(lexemes[++(*i)], H_DEL, metadata), 1);
	heredoc(node->tok, node->next->tok->lex);
	handle_signal();
	return ;
}

int	received_sigint(int *fds, char *input)
{
	if (last_exit_status(-1) == 130)
	{
		dup2(fds[1], STDIN_FILENO);
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

int	is_delimiter(char *delimiter, char *input)
{
	if (!(!input))
	{
		if (*input)
		{
			if (!ft_strncmp(delimiter, input, ft_strlen(input)))
			{
				free(input);
				return (TRUE);
			}
		}
		return (FALSE);
	}
	else
		return (FALSE);
}

int	warn_heredoc(char *input, char *delimiter)
{
	if (!input)
	{
		ft_putstr_fd("heredoc: warning: here-document \
delimited by end-of-file (wanted \'", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("\')\n", 2);
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

int	open_fds_heredoc(char *file, int *fds)
{
	fds[1] = dup(STDIN_FILENO);
	if (fds[1] == -1)
		return (TRUE);
	fds[0] = ft_open_fd(file, OPEN_WR);
	if (fds[0] == -1)
	{
		close(fds[1]);
		free(file);
		return (TRUE);
	}
	return (FALSE);
}
