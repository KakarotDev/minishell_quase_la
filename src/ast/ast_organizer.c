/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_organizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:28:57 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/12 00:27:54 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command_organizer(t_ast *raiz, t_pipex *p)
{
	p->fd_exec[1] = p->pipe_fd[1];
	p->fd_exec[0] = STDIN_FILENO;
	exec_cmd(raiz->esq, p);
	closing_process(p, raiz);
}

void	standard_command_organizer(t_ast *raiz, t_pipex *p)
{
	//if (raiz->dir->index != 3)
	p->fd_exec[1] = p->exit_fd;
	p->fd_exec[0] = p->input_fd;
	exec_cmd(raiz->dir, p);
	if (raiz->index == 3)
	{
		close(p->pipe_fd[1]);
		close(p->pipe_fd[0]);
	}
}

void	brothers_functions(t_dlist **tokens, t_pipex *p)
{
	t_ast	*raiz;

	raiz = cria_arvore(tokens, p);
	free(tokens);
	raiz->first = raiz;
	tree_exec(raiz, p, STDOUT_FILENO);
	//tree_exec(raiz, p, STDOUT_FILENO);
	//printf("TESTE=%d\n", get_ret_process(-1));
	//waitpid(-1, NULL, 0);
	//wait(NULL);
	closing_father(p, raiz);
}

int	execv_only_child(t_ast *root, t_pipex *p)
{
	int	exit_status;

	p->f_id_exec = fork();
	exit_status = 0;
	if (p->f_id_exec == 0)
	{
		if (root->r_fds.r_fd_out != 0)
			dup2(p->fd_exec[1], 1);
		if (root->r_fds.r_fd_in != 0)
			dup2(p->fd_exec[0], 0);
		close_fds(1024);
		execve(root->path, root->cmd, hook_environ(NULL, 0));
		execve_error_exit(root);
	}
	waitpid(p->f_id_exec, &exit_status, 0);
	return (exit_status);
}

void	only_child_functions(t_dlist **tokens, t_pipex *p)
{
	t_ast	*root;
	int		exit_status;

	root = cria_no_cmd(*tokens, p, 0, 0);
	root->r_fds = r_fds_control(root, p);
	if (*root->cmd && (builtins_checker(root) < 0))
	{
		exit_status = command_not_found(root->path, root->cmd);
		if (!exit_status && root->path && **root->cmd)
			exit_status = execv_only_child(root, p);
	}
	else
		builtins_caller(root, p, 1);
	closing_only_child(p, root, tokens[0]);
	free(tokens);
}
