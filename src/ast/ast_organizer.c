/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_organizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:28:57 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/13 19:52:15 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command_organizer(t_ast *raiz, t_pipex *p)
{
	dup2(p->pipe_fd[1], STDOUT_FILENO);
	close(p->pipe_fd[1]);
	close(p->pipe_fd[0]);
	exec_cmd(raiz->esq, p);
	closing_process(p, raiz);
}

void	standard_command_organizer(t_ast *raiz, t_pipex *p)
{
	dup2(p->pipe_fd[0], STDIN_FILENO);
	close(p->pipe_fd[1]);
	close(p->pipe_fd[0]);
	exec_cmd(raiz->dir, p);
}

void	brothers_functions(t_dlist **tokens, t_pipex *p)
{
	t_ast	*raiz;

	raiz = cria_arvore(tokens, p);
	free(tokens);
	raiz->first = raiz;
	tree_exec(raiz, p, STDOUT_FILENO);
	closing_father(p, raiz);
}

int	execv_only_child(t_ast *root, t_pipex *p)
{
	int	exit_status;
	int	pid;

	pid = fork();
	exit_status = 0;
	if (pid == 0)
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
		execve(root->path, root->cmd, hook_environ(NULL, 0));
		execve_error_exit(root);
	}
	waitpid(pid, &exit_status, 0);
	return (exit_status);
}

void	only_child_functions(t_dlist **tokens, t_pipex *p)
{
	t_ast	*root;
	int		exit_status;

	root = cria_no_cmd(*tokens, p, 0, 0);
	redir_fds_control(root, p);
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
