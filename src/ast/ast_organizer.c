/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_organizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:28:57 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/25 16:47:32 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_pipes_fd(int *pipe_fds, int side)
{
	if (side == LEFT)
		dup2(pipe_fds[1], STDOUT_FILENO);
	else if (side == RIGHT)
		dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

void	tree_exec_pipe_procedure(t_ast *root, int pipe_fds[2])
{
	is_process(TRUE);
	root->left->first_leaf = root->first_leaf;
	manage_pipes_fd(pipe_fds, LEFT);
	tree_exec(root->left);
	closing_process(root);
}

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

void	only_child_functions(t_dlist **tokens)
{
	t_ast	*root;
	int		exit_status;

	root = create_cmd_leaf(*tokens);
	root->first_leaf = root;
	free_chunk_list(*tokens);
	free(tokens);
	if (!redir_fds_control(root))
	{
		if (*root->cmd_matrix && (builtins_checker(root) < 0))
		{
			exit_status = path_validation(root->path, root->cmd_matrix);
			if (!exit_status && root->path && **root->cmd_matrix)
				execv_only_child(root);
		}
		else if (*root->cmd_matrix)
			builtins_caller(root);
	}
	closing_only_child(root);
}
