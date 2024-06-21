/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:05:29 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/20 19:16:20 by parthur-         ###   ########.fr       */
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
