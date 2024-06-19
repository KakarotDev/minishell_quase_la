/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:00:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/18 20:39:07 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast(t_dlist **tokens)
{
	t_ast	*root;
	t_ast	*left;
	t_dlist	*aux;
	int		i;

	i = tokens[0]->pipes;
	aux = tokens[0];
	root = NULL;
	while (i >= 0)
	{
		if (i > 0)
		{
			left = create_pipe_leaf(aux);
			aux = free_chunk_list(tokens[0]);
			root = append_leaf(root, left);
		}
		else
		{
			left = create_cmd_leaf(aux);
			aux = free_chunk_list(tokens[0]);
			root = append_leaf(root, left);
		}
		i--;
	}
	return (root);
}

void	execv_pipes(t_ast *root)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
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
		if (execve(root->path, root->cmd_matrix, hook_environ(NULL, 0)) == -1)
			execve_error_exit(root->first_leaf);
	}
	last_exit_status(get_ret_process(pid));
}

void	exec_cmd(t_ast *root)
{
	int		exit_status;

	if (redir_fds_control(root))
		return ;
	if (*root->cmd_matrix && (builtins_checker(root) < 0))
	{
		exit_status = path_validation(root->path, root->cmd_matrix);
		if (!exit_status && root->path && **root->cmd_matrix)
			execv_pipes(root);
	}
	else if (*root->cmd_matrix)
		builtins_caller(root);
}

void	manage_pipes_fd(int *pipe_fds, int side)
{
	if (side == LEFT)
		dup2(pipe_fds[1], STDOUT_FILENO);
	else if (side == RIGHT)
		dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

void	tree_exec_termination(int pipe_fds[2], int forks[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	get_ret_process(forks[0]);
	last_exit_status(get_ret_process(forks[1]));
}

void	tree_exec_pipe_procedure(t_ast *root, int pipe_fds[2])
{
	is_process(TRUE);
	root->left->first_leaf = root->first_leaf;
	manage_pipes_fd(pipe_fds, LEFT);
	tree_exec(root->left);
	closing_process(root);
}

void	tree_exec(t_ast *root)
{
	int	pipe_fds[2];
	int	forks[2];

	forks[0] = 0;
	forks[1] = 0;
	if (pipe(pipe_fds) == -1)
		return ;
	if (root->left->type == PIPE)
	{
		forks[0] = fork();
		if (forks[0] == 0)
			tree_exec_pipe_procedure(root, pipe_fds);
		forks[1] = fork();
		if (forks[1] == 0)
			command_organizer(root, pipe_fds, RIGHT);
	}
	else
	{
		forks[0] = fork();
		if (forks[0] == 0)
			command_organizer(root, pipe_fds, LEFT);
		forks[1] = fork();
		if (forks[1] == 0)
			command_organizer(root, pipe_fds, RIGHT);
	}
	tree_exec_termination(pipe_fds, forks);
}

void	ast_function(t_dlist **tokens)
{
	tokens[0]->pipes = pipe_count(tokens[0]);
	expansion(tokens);
	quote_removal(tokens);
	if (tokens[0]->pipes > 0)
		brothers_functions(tokens);
	else
		only_child_functions(tokens);
}
