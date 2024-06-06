/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:00:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/06 18:38:51 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*cria_arvore(t_dlist **t, t_pipex *p)
{
	t_ast	*raiz;
	t_ast	*esq;
	t_dlist	*aux;
	int		i;

	i = t[0]->pipes;
	aux = t[0];
	raiz = NULL;
	while (i >= 0)
	{
		if (i > 0)
		{
			esq = cria_no_arv(aux, p, i, t[0]->pipes);
			aux = free_chunk_list(t[0]);
			raiz = adiciona_no(raiz, esq);
		}
		else
		{
			esq = cria_no_cmd(aux, p, i, t[0]->pipes);
			aux = free_chunk_list(t[0]);
			raiz = adiciona_no(raiz, esq);
		}
		i--;
	}
	return (raiz);
}

void	execv_pipes(t_ast *root, t_pipex *p)
{
	int	f_id;

	f_id = fork();
	if (f_id == 0)
	{
		if (root->index != 3 || root->r_fds.r_fd_out != 0)
			dup2(p->fd_exec[1], 1);
		if (root->index != 1 || root->r_fds.r_fd_in != 0)
			dup2(p->fd_exec[0], 0);
		close_fds(1024);
		if (execve(root->path, root->cmd, hook_environ(NULL, 0)) == -1)
			exit(last_exit_status(-1));
	}
}

void	exec_cmd(t_ast *raiz, t_pipex *p)
{
	int		exit_status;

	raiz->r_fds = r_fds_control(raiz, p);
	if (*raiz->cmd && (builtins_checker(raiz) < 0))
	{
		exit_status = command_not_found(raiz->path, raiz->cmd);
		if (!exit_status && raiz->path && **raiz->cmd)
			execv_pipes(raiz, p);
	}
	else
		exit_status = builtins_caller(raiz, p, 0);
	if (raiz->index != 1)
		close(p->fd_exec[0]);
	if (raiz->index != 3)
		close(p->fd_exec[1]);
}

void	tree_exec(t_ast *raiz, t_pipex *p, int fd)
{
	p->exit_fd = fd;
	if (pipe(p->pipe_fd) == -1)
		return ;
	p->input_fd = p->pipe_fd[0];
	if (raiz->esq->type == PIPE)
	{
		p->f_id = fork();
		if (p->f_id == 0)
		{
			fd = p->pipe_fd[1];
			raiz->esq->first = raiz->first;
			tree_exec(raiz->esq, p, fd);
			closing_process(p, raiz);
		}
		waitpid(p->f_id, NULL, 0);
	}
	else
	{
		p->f_id = fork();
		if (p->f_id == 0)
			first_command_organizer(raiz, p);
		waitpid(p->f_id, NULL, 0);
	}
	standard_command_organizer(raiz, p);
}

void	ast_function(t_dlist **tokens)
{
	t_pipex	*p;

	tokens[0]->pipes = have_pipe(tokens[0]);
	p = (t_pipex *)ft_calloc(sizeof(t_pipex), 1);
	expansion(tokens);
	quote_removal(tokens);
	get_paths(p);
	if (tokens[0]->pipes > 0)
		brothers_functions(tokens, p);
	else
		only_child_functions(tokens, p);
}
