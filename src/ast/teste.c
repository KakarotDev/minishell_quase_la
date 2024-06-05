/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 23:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    t_ast    *root;
    int        exit_status;

    root = cria_no_cmd(*tokens, p, 0, 0);
    root->r_fds = r_fds_control(root, p);
    if (*root->cmd && (builtins_caller(root->cmd, root, p) == -1))
    {
        exit_status = command_not_found(root->path, root->cmd);
        if (!exit_status && root->path && **root->cmd)
        {
            p->f_id = fork();
            if (p->f_id == 0)
            {
                //root->r_fds = r_fds_control(root, p);
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
    else
    {
        if (root->r_fds.r_fd_out != 0)
            dup2(1, p->fd_exec[1]);
        if (root->r_fds.r_fd_in != 0)
            dup2(0, p->fd_exec[0]);
        close_fds(1024);
    }
    closing_only_child(p, root, tokens);
}

//criar dinamica dos redirects no caso de builtins, caso for only child, voltar a dup
//adicionar no closing a função que ira captar o 