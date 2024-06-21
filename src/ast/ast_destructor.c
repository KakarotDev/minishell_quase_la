/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:05:12 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/20 19:18:05 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_exec_termination(int pipe_fds[2], int forks[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	get_ret_process(forks[0]);
	last_exit_status(get_ret_process(forks[1]));
}

void	closing_only_child(t_ast *root)
{
	if (root->redir_fds[0] > 0)
		close(root->redir_fds[0]);
	if (root->redir_fds[1] > 0)
		close(root->redir_fds[1]);
	ft_free_ast(root);
}

void	closing_process(t_ast *root)
{
	if (root->redir_fds[0] != 0)
		close(root->redir_fds[0]);
	if (root->redir_fds[1] != 0)
		close(root->redir_fds[1]);
	ft_free_ast(root->first_leaf);
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	exit(last_exit_status(-1));
}

void	execve_error_exit(t_ast *root)
{
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	ft_free_ast(root);
	exit(1);
	return ;
}
