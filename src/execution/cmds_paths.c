/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:03 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 19:39:54 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(void)
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

static char	*create_path(t_dlist *tokens)
{
	t_dlist	*aux;
	char	*path;
	char	**paths_matrix;
	int		i;

	i = 0;
	aux = go_to_first_word(tokens);
	if (ft_strchr(aux->tok->lex, '/'))
		return (ft_strdup(aux->tok->lex));
	paths_matrix = get_paths();
	if (!paths_matrix)
		return (NULL);
	while (paths_matrix[i] != NULL && aux->tok->type == WORD && aux->tok->lex)
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

static char	**defining_commands(t_dlist *tokens, size_t mat_exec_len)
{
	char	**cmd_matrix;
	int		i;

	i = 0;
	cmd_matrix = ft_calloc(sizeof(char *), mat_exec_len);
	while (tokens != NULL)
	{
		if (tokens->tok->type == WORD && tokens->tok->lex)
		{
			cmd_matrix[i] = ft_strdup(tokens->tok->lex);
			i++;
		}
		tokens = tokens->next;
	}
	return (cmd_matrix);
}

static char	**create_cmd_matrix(t_dlist *tokens)
{
	t_dlist	*aux;
	char	**cmd_matrix;
	size_t	cmd_matrix_lenght;

	cmd_matrix_lenght = 1;
	if (!tokens)
		return (NULL);
	aux = tokens;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == WORD && aux->tok->lex)
			cmd_matrix_lenght++;
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	cmd_matrix = defining_commands(aux, cmd_matrix_lenght);
	return (cmd_matrix);
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
