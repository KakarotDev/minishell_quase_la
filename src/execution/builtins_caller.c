/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_caller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/05 17:42:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fd_for_builtins(t_ast *root, t_pipex *p,
			int control, int exit_status)
{
	if (control == 0)
	{
		root->r_fds = r_fds_control(root, p);
		if (root->index != 3 || root->r_fds.r_fd_out != 0)
    		dup2(p->fd_exec[1], STDOUT_FILENO);
   		else if (root->index != 1 || root->r_fds.r_fd_in != 0)
       		dup2(p->fd_exec[0], STDIN_FILENO);
	}
	if (control == 1 && exit_status != -1)
	{
		if (root->r_fds.r_fd_out != 0)
        	dup2(p->save_fd[1], STDOUT_FILENO);
   		else if (root->r_fds.r_fd_in != 0)
        	dup2(p->save_fd[0], STDIN_FILENO);
		close_fds(1024);
	}
}

int	builtins_caller(t_ast *root, t_pipex *p)
{
	int	exit_status;

	exit_status = -1;
	p->save_fd[0] = dup(STDIN_FILENO);
	p->save_fd[1] = dup(STDOUT_FILENO);
	save_fd_for_builtins(root, p, 0, 1);
	if (!ft_strncmp(root->cmd[0], "echo", ft_strlen(root->cmd[0])))
		exit_status = echo(root->cmd);
	else if (!ft_strncmp(root->cmd[0], "export", ft_strlen(root->cmd[0])))
		exit_status = export(root->cmd);
	else if (!ft_strncmp(root->cmd[0], "cd", ft_strlen(root->cmd[0])))
		exit_status = cd(root->cmd);
	else if (!ft_strncmp(root->cmd[0], "env", ft_strlen(root->cmd[0])))
		exit_status = env(root->cmd);
	else if (!ft_strncmp(root->cmd[0], "pwd", ft_strlen(root->cmd[0])))
		exit_status = pwd();
	else if (!ft_strncmp(root->cmd[0], "exit", ft_strlen(root->cmd[0])))
		exit_status = builtin_exit(root->cmd);
	else if (!ft_strncmp(root->cmd[0], "unset", ft_strlen(root->cmd[0])))
		exit_status = unset(root->cmd);
	save_fd_for_builtins(root, p, 1, exit_status);
	if (exit_status != -1)
		return (last_exit_status(exit_status));
	return (exit_status);
}
