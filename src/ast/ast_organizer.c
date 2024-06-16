/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_organizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:28:57 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/16 05:38:12 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	first_command_organizer(t_ast *root, int pipe_fds[2])
// {
// 	manage_pipes_fd(pipe_fds, LEFT);
// 	exec_cmd(root);
// 	closing_process(root);
// }

void	command_organizer(t_ast *root, int pipe_fds[2], int side)
{
	is_process(TRUE);
	if (side == LEFT)
	{
		root->left->first_leaf = root->first_leaf;
		manage_pipes_fd(pipe_fds, LEFT);
		exec_cmd(root->left);
		closing_process(root->left);
	}
	else if (side == RIGHT)
	{
		root->right->first_leaf = root->first_leaf;
		manage_pipes_fd(pipe_fds, RIGHT);
		exec_cmd(root->right);
		closing_process(root->right);
	}
}

void	brothers_functions(t_dlist **tokens)
{
	t_ast	*root;

	root = create_ast(tokens);
	root->first_leaf = root;
	free(tokens);
	tree_exec(root);
	ft_free_ast(root);
}

void	execv_only_child(t_ast *root)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		is_process(TRUE);
		if (root->redir_fds[1] != 0)
		{
			dup2(root->redir_fds[1], STDOUT_FILENO);
			close(root->redir_fds[1]);
		}		
		if (root->redir_fds[0] != 0)
		{
			dup2(root->redir_fds[0], STDIN_FILENO);
			close(root->redir_fds[0]);
		}
		signal(SIGQUIT, SIG_DFL);
		if (execve(root->path, root->cmd_matrix, hook_environ(NULL, 0)))
			execve_error_exit(root);
	}
	last_exit_status(get_ret_process(pid));
}

void	only_child_functions(t_dlist **tokens)
{
	t_ast	*root;
	int		exit_status;

	root = create_cmd_leaf(*tokens);
	redir_fds_control(root);
	if (!root)
		return ;
	if (*root->cmd_matrix && (builtins_checker(root) < 0))
	{
		exit_status = command_not_found(root->path, root->cmd_matrix);
		if (!exit_status && root->path && **root->cmd_matrix)
			execv_only_child(root);
	}
	else if (*root->cmd_matrix)
		builtins_caller(root);
	closing_only_child(root, tokens);
}
