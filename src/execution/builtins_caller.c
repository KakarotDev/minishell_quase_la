/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_caller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 01:55:27 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fd_for_builtins(t_ast *root, int control)
{
	static int	fd_stdout;

	if (control == 0)
	{
		fd_stdout = dup(STDOUT_FILENO);
		if (root->redir_fds[1] != 0)
		{
			dup2(root->redir_fds[1], STDOUT_FILENO);
			close(root->redir_fds[1]);
		}
	}
	else if (control == 1)
	{
		if (!is_process(-1))
		{
			if (root->redir_fds[1] != 0)
				dup2(fd_stdout, STDOUT_FILENO);
		}
		close(fd_stdout);
	}
}

int	builtins_checker(t_ast *root)
{
	int	exit_status;

	exit_status = -1;
	if (!ft_strcmp(root->cmd_matrix[0], "echo"))
		exit_status = 1;
	else if (!ft_strcmp(root->cmd_matrix[0], "export"))
		exit_status = 1;
	else if (!ft_strcmp(root->cmd_matrix[0], "cd"))
		exit_status = 1;
	else if (!ft_strcmp(root->cmd_matrix[0], "env"))
		exit_status = 1;
	else if (!ft_strcmp(root->cmd_matrix[0], "pwd"))
		exit_status = 1;
	else if (!ft_strcmp(root->cmd_matrix[0], "exit"))
		exit_status = 1;
	else if (!ft_strcmp(root->cmd_matrix[0], "unset"))
		exit_status = 1;
	return (exit_status);
}

void	builtins_caller(t_ast *root)
{
	int	exit_status;

	exit_status = 0;
	save_fd_for_builtins(root, 0);
	if (!ft_strcmp(root->cmd_matrix[0], "echo"))
		exit_status = echo(root->cmd_matrix);
	else if (!ft_strcmp(root->cmd_matrix[0], "export"))
		exit_status = export(root->cmd_matrix);
	else if (!ft_strcmp(root->cmd_matrix[0], "cd"))
		exit_status = cd(root->cmd_matrix);
	else if (!ft_strcmp(root->cmd_matrix[0], "env"))
		exit_status = env(root->cmd_matrix);
	else if (!ft_strcmp(root->cmd_matrix[0], "pwd"))
		exit_status = pwd();
	else if (!ft_strcmp(root->cmd_matrix[0], "exit"))
		exit_status = builtin_exit(root->cmd_matrix);
	else if (!ft_strcmp(root->cmd_matrix[0], "unset"))
		exit_status = unset(root->cmd_matrix);
	save_fd_for_builtins(root, 1);
	last_exit_status(exit_status);
}
