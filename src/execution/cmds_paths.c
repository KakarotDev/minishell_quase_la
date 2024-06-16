/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:03 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/16 04:07:22 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(void)
{
	int		index;
	char	*temp_string;
	char	*paths_string;
	char	**paths_matrix;

	index = 0;
	paths_string = ft_getenv("PATH");
	if (!paths_string)
		return (NULL);
	paths_matrix = ft_split(paths_string, ':');
	free(paths_string);
	while (paths_matrix[index])
	{
		temp_string = ft_strjoin(paths_matrix[index], "/");
		free(paths_matrix[index]);
		paths_matrix[index] = temp_string;
		index++;
	}
	return (paths_matrix);
}

char	*create_path(t_dlist *tokens)
{
	t_dlist	*aux;
	char	*path;
	char	**paths_matrix;
	int		i;

	i = 0;
	aux = tokens;
	aux = go_to_pipe_or_first(aux);
	aux = go_to_first_word(aux);
	if (ft_strchr(aux->tok->lex, '/'))
		return (ft_strdup(aux->tok->lex));
	paths_matrix = get_paths();
	while (paths_matrix[i] != NULL && aux->tok->type == WORD)
	{
		path = ft_strjoin(paths_matrix[i], aux->tok->lex);
		if (access(path, X_OK) == 0)
		{
			ft_free_matrix((void **) paths_matrix);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_matrix((void **) paths_matrix);
	return (NULL);
}

char	**defining_commands(t_dlist *tokens, size_t mat_exec_len)
{
	char	**cmd_matrix;
	int		i;

	i = 0;
	cmd_matrix = ft_calloc(sizeof(char *), mat_exec_len);
	while (tokens != NULL)
	{
		if (tokens->tok->type == WORD)
		{
			cmd_matrix[i] = ft_strdup(tokens->tok->lex);
			i++;
		}
		tokens = tokens->next;
	}
	return (cmd_matrix);
}

char	**create_cmd_matrix(t_dlist *tokens)
{
	t_dlist	*aux;
	char	**mat_exc;
	size_t	mat_exec_len;

	mat_exec_len = 1;
	aux = tokens;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == WORD)
			mat_exec_len++;
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	mat_exc = defining_commands(aux, mat_exec_len);
	return (mat_exc);
}

t_ast	*create_cmd_leaf(t_dlist *tokens)
{
	t_ast	*cmd_leaf;

	cmd_leaf = (t_ast *) malloc(sizeof(t_ast));
	cmd_leaf->type = WORD;
	cmd_leaf->left = NULL;
	cmd_leaf->right = NULL;
	cmd_leaf->path = create_path(tokens);
	cmd_leaf->cmd_matrix = create_cmd_matrix(tokens);
	cmd_leaf->files = have_redirect(tokens);
	cmd_leaf->redir_fds[0] = 0;
	cmd_leaf->redir_fds[1] = 0;
	return (cmd_leaf);
}
