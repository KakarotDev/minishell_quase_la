/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:00:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/13 19:43:07 by parthur-         ###   ########.fr       */
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
	p->f_id_grandchild = fork();
	if (p->f_id_grandchild == 0)
	{
		if (p->redir_fds[1] != 0)
		{
			dup2(p->redir_fds[1], STDOUT_FILENO);
			close(p->redir_fds[1]);
		}
		if (p->redir_fds[0] != 0)
		{
			dup2(p->redir_fds[0], STDIN_FILENO);
			close(p->redir_fds[0]);
		}
		if (execve(root->path, root->cmd, hook_environ(NULL, 0)) == -1)
			exit(last_exit_status(-1));
	}
	waitpid(p->f_id_grandchild, NULL, 0);
}

void	exec_cmd(t_ast *raiz, t_pipex *p)
{
	int		exit_status;

	redir_fds_control(raiz, p);
	if (*raiz->cmd && (builtins_checker(raiz) < 0))
	{
		exit_status = command_not_found(raiz->path, raiz->cmd);
		if (!exit_status && raiz->path && **raiz->cmd)
			execv_pipes(raiz, p);
	}
	else
		exit_status = builtins_caller(raiz, p, 0);
}

void	tree_exec(t_ast *raiz, t_pipex *p, int fd)
{
	if (pipe(p->pipe_fd) == -1)
		return ;
	if (raiz->esq->type == PIPE)
	{
		p->f_id_left = fork();
		if (p->f_id_left == 0)
		{
			raiz->esq->first = raiz->first;
			dup2(p->pipe_fd[1], STDOUT_FILENO);
			close(p->pipe_fd[1]);
			close(p->pipe_fd[0]);
			tree_exec(raiz->esq, p, fd);
			closing_process(p, raiz);
		}
		p->f_id_right = fork();
		if (p->f_id_right == 0)
		{
			standard_command_organizer(raiz, p);
			closing_process(p, raiz);
		}
	}
	else
	{
		p->f_id_left = fork();
		if (p->f_id_left == 0)
		{
			first_command_organizer(raiz, p);
		}
		p->f_id_right = fork();
		if (p->f_id_right == 0)
		{
			standard_command_organizer(raiz, p);
			closing_process(p, raiz);
		}
	}
	close(p->pipe_fd[1]);
	close(p->pipe_fd[0]);
	waitpid(p->f_id_left, NULL, 0);
	waitpid(p->f_id_right, NULL, 0);
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
