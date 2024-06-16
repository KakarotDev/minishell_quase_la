/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:08:18 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/23 18:08:18 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_dlist *tokens)
{
	free(tokens->tok->heredoc_file);
	free(tokens->tok->lex);
	free(tokens->tok);
	free(tokens);
}

void	closing_process(t_ast *root)
{
	if (root->redir_fds[0] != 0)
		close(root->redir_fds[0]);
	if (root->redir_fds[1] != 0)
		close(root->redir_fds[1]);
	ft_free_ast(root->first_leaf);
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	exit(last_exit_status(-1));
}

void	free_right(t_ast *right)
{
	ft_free_matrix_char(right->cmd_matrix);
	free(right->path);
	if (right->files[0])
		ft_free_matrix_char(right->files[0]);
	if (right->files[1])
		ft_free_matrix_char(right->files[1]);
	if (right->files[2])
		ft_free_matrix_char(right->files[2]);
	free(right->files);
	right->files = NULL;
	right->cmd_matrix = NULL;
	right->path = NULL;
}

void	ft_free_ast(t_ast *root)
{
	if (root->left != NULL)
		ft_free_ast(root->left);
	else
		free_right(root);
	if (root->right != NULL)
	{
		free_right(root->right);
		free(root->right);
	}
	free(root);
}

t_dlist	*free_chunk_list(t_dlist *tokens)
{
	while (tokens->next != NULL)
		tokens = tokens->next;
	while (tokens->tok->type != PIPE && tokens->prev)
	{
		tokens = tokens->prev;
		free_tokens(tokens->next);
	}
	if (tokens->prev)
	{
		tokens = tokens->prev;
		free_tokens(tokens->next);
		tokens->next = NULL;
	}
	else
	{
		free_tokens(tokens);
		tokens = NULL;
	}
	return (tokens);
}
