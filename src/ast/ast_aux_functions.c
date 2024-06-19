/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:24:33 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/18 21:34:17 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	closing_father(t_ast *root)
// {
// 	ft_free_ast(root);
// }

void	closing_only_child(t_ast *root)
{
	if (root->redir_fds[0] > 0)
		close(root->redir_fds[0]);
	if (root->redir_fds[1] > 0)
		close(root->redir_fds[1]);
	ft_free_ast(root);
}

t_ast	*create_pipe_leaf(t_dlist *tokens)
{
	t_ast	*pipe_leaf;

	pipe_leaf = (t_ast *)malloc(sizeof(t_ast));
	pipe_leaf->type = PIPE;
	pipe_leaf->left = NULL;
	pipe_leaf->right = create_cmd_leaf(tokens);
	pipe_leaf->path = NULL;
	pipe_leaf->cmd_matrix = NULL;
	pipe_leaf->redir_fds[0] = 0;
	pipe_leaf->redir_fds[1] = 0;
	return (pipe_leaf);
}

t_ast	*append_leaf(t_ast *root, t_ast *leaf)
{
	if (root == NULL)
		return (leaf);
	root->left = append_leaf(root->left, leaf);
	return (root);
}

void	execve_error_exit(t_ast *root)
{
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	ft_free_ast(root);
	exit(1);
	return ;
}
