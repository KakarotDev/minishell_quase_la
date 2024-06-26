/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:06:37 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 19:38:01 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	execv_pipes(t_ast *root)
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

void	tree_exec(t_ast *root)
{
	t_exec_aux	aux;

	aux.forks[0] = 0;
	aux.forks[1] = 0;
	if (pipe(aux.pipe_fds) == -1)
		return ;
	if (root->left->type == PIPE)
	{
		aux.forks[0] = fork();
		if (aux.forks[0] == 0)
			tree_exec_pipe_procedure(root, aux.pipe_fds);
		aux.forks[1] = fork();
		if (aux.forks[1] == 0)
			command_organizer(root, aux.pipe_fds, RIGHT);
	}
	else
	{
		aux.forks[0] = fork();
		if (aux.forks[0] == 0)
			command_organizer(root, aux.pipe_fds, LEFT);
		aux.forks[1] = fork();
		if (aux.forks[1] == 0)
			command_organizer(root, aux.pipe_fds, RIGHT);
	}
	tree_exec_termination(aux.pipe_fds, aux.forks);
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
