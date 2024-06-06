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
	free(tokens->tok->lex);
	free(tokens->tok);
	free(tokens);
}

void	closing_process(t_pipex *p, t_ast *raiz)
{
	close_fds(1024);
	ft_free_matrix_char(p->paths.mat_path);
	free(p);
	ft_free_ast(raiz->first);
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	exit(0);
}

void	free_right(t_ast *right)
{
	ft_free_matrix_char(right->cmd);
	free(right->path);
	if (right->files[0])
		ft_free_matrix_char(right->files[0]);
	if (right->files[1])
		ft_free_matrix_char(right->files[1]);
	if (right->files[2])
		ft_free_matrix_char(right->files[2]);
	free(right->files);
	right->files = NULL;
	right->cmd = NULL;
	right->path = NULL;
}

void	ft_free_ast(t_ast *root)
{
	if (root->esq != NULL)
		ft_free_ast(root->esq);
	else
		free_right(root);
	if (root->dir != NULL)
	{
		free_right(root->dir);
		free(root->dir);
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
