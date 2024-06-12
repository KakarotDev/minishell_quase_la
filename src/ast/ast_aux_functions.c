/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:24:33 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/11 23:30:01 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closing_father(t_pipex *p, t_ast *raiz)
{
	ft_free_ast(raiz);
	ft_free_matrix_char(p->paths.mat_path);
	free(p);
	close_fds(1024);
}

void	closing_only_child(t_pipex *p, t_ast *raiz, t_dlist *tokens)
{
	ft_free_matrix_char(p->paths.mat_path);
	free(p);
	ft_free_ast(raiz);
	free_chunk_list(tokens);
}

t_ast	*cria_no_arv(t_dlist *tokens, t_pipex *p, int i, int t)
{
	t_ast	*no_pipe;

	no_pipe = (t_ast *)malloc(sizeof(t_ast));
	no_pipe->type = PIPE;
	no_pipe->esq = NULL;
	no_pipe->dir = cria_no_cmd(tokens, p, i, t);
	no_pipe->path = NULL;
	no_pipe->cmd = NULL;
	no_pipe->index = 0;
	return (no_pipe);
}

t_ast	*adiciona_no(t_ast *raiz, t_ast *no)
{
	if (raiz == NULL)
		return (no);
	raiz->esq = adiciona_no(raiz->esq, no);
	return (raiz);
}

void	execve_error_exit(t_ast *root)
{
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	ft_free_ast(root);
	exit(last_exit_status(-1));
	return ;
}
