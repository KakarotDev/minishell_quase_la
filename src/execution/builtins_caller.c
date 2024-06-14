/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_caller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/14 19:44:58 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fd_for_builtins(t_pipex *p, int control)
{
	if (control == 0)
	{
		if (p->redir_fds[1] != 0)
		{
			dup2(p->redir_fds[1], STDOUT_FILENO);
			close(p->redir_fds[1]);
		}
	}
	if (control == 1)
	{
		if (p->redir_fds[1] != 0)
			dup2(p->save_fd[1], STDOUT_FILENO);
	}
}

int	builtins_checker(t_ast *root)
{
	int	exit_status;

	exit_status = -1;
	if (!ft_strncmp(root->cmd[0], "echo", ft_strlen(root->cmd[0])))
		exit_status = 1;
	else if (!ft_strncmp(root->cmd[0], "export", ft_strlen(root->cmd[0])))
		exit_status = 1;
	else if (!ft_strncmp(root->cmd[0], "cd", ft_strlen(root->cmd[0])))
		exit_status = 1;
	else if (!ft_strncmp(root->cmd[0], "env", ft_strlen(root->cmd[0])))
		exit_status = 1;
	else if (!ft_strncmp(root->cmd[0], "pwd", ft_strlen(root->cmd[0])))
		exit_status = 1;
	else if (!ft_strncmp(root->cmd[0], "exit", ft_strlen(root->cmd[0])))
		exit_status = 1;
	else if (!ft_strncmp(root->cmd[0], "unset", ft_strlen(root->cmd[0])))
		exit_status = 1;
	return (exit_status);
}

int	builtins_caller(t_ast *root, t_pipex *p, int control)
{
	int	exit_status;

	exit_status = -1;
	p->save_fd[1] = dup(STDOUT_FILENO);
	save_fd_for_builtins(p, 0);
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
	if (control == 1)
		save_fd_for_builtins(p, 1);
	close_fds(p->save_fd[1]);
	if (exit_status != -1)
		return (last_exit_status(exit_status));
	return (exit_status);
}
