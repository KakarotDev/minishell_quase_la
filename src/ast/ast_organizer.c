/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_organizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:28:57 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/05 14:34:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command_organizer(t_ast *raiz, t_pipex *p)
{
	p->fd_exec[1] = p->pipe_fd[1];
	p->fd_exec[0] = 0;
	exec_cmd(raiz->esq, p);
	closing_process(p, raiz);
}

void	standard_command_organizer(t_ast *raiz, t_pipex *p)
{
	if (raiz->dir->index != 3)
		p->fd_exec[1] = p->exit_fd;
	p->fd_exec[0] = p->input_fd;
	exec_cmd(raiz->dir, p);
	if (raiz->dir->index == 3)
		close(p->pipe_fd[1]);
}

void	brothers_functions(t_dlist **tokens, t_pipex *p)
{
	t_ast	*raiz;

	raiz = cria_arvore(tokens, p);
	free(tokens);
	raiz->first = raiz;
	tree_exec(raiz, p, STDOUT_FILENO);
	wait(NULL);
	closing_father(p, raiz);
}

//void	only_child_functions(t_dlist **tokens, t_pipex *p)
//{
//	t_ast	*raiz;
//
//	raiz = cria_no_cmd(tokens[0], p, 0, 0);
//	p->f_id = fork();
//	if (p->f_id == 0)
//	{
//		free_chunk_list(tokens[0]);
//		free(tokens);
//		raiz->first = raiz;
//		raiz->r_fds = r_fds_control(raiz, p);
//		if (raiz->r_fds.r_fd_out != 0)
//			dup2(p->fd_exec[1], 1);
//		if (raiz->r_fds.r_fd_in != 0)
//			dup2(p->fd_exec[0], 0);
//		close_fds(1024);
//		if (execve(raiz->path, raiz->cmd, hook_environ(NULL, 0)) == -1)
//			exit(last_exit_status(-1));
//	}
//	waitpid(-1, NULL, 0);
//	closing_only_child(p, raiz, tokens[0]);
//	free(tokens);
//}

void    execve_error_exit(t_ast *root)
{
    hook_environ(NULL, 1);
    hook_pwd(NULL, 1);
    ft_free_ast(root);
    exit(last_exit_status(-1));
    return ;
}


void    only_child_functions(t_dlist **tokens, t_pipex *p)
{
    t_ast	*root;
    int		exit_status;

    root = cria_no_cmd(*tokens, p, 0, 0);
    root->r_fds = r_fds_control(root, p);
    if (*root->cmd && (builtins_caller(root, p) < 0))
    {
        exit_status = command_not_found(root->path, root->cmd);
        if (!exit_status && root->path && **root->cmd)
        {
            p->f_id = fork();
            if (p->f_id == 0)
            {
                if (root->r_fds.r_fd_out != 0)
                    dup2(p->fd_exec[1], 1);
                if (root->r_fds.r_fd_in != 0)
                    dup2(p->fd_exec[0], 0);
                close_fds(1024);
                if (execve(root->path, root->cmd, hook_environ(NULL, 0)) == -1)
                    execve_error_exit(root);
            }
            waitpid(p->f_id, &exit_status, 0);
        }
    }
    closing_only_child(p, root, tokens[0]);
	free(tokens);
}
