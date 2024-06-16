/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:03:17 by marvin            #+#    #+#             */
/*   Updated: 2024/05/24 17:03:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_fds_control(t_ast *root)
{
	int	status;

	status = 0;
	if (root->files[0] != NULL)
	{
		status = files_in_control(root);
		if (status)
			return (EXIT_FAILURE);
	}
	else
		root->redir_fds[0] = 0;
	if (!status && root->files[1] != NULL)
	{
		status = files_out_control(root);
		if (status)
			return (EXIT_FAILURE);
	}
	else
		root->redir_fds[1] = 0;
	return (EXIT_SUCCESS);
}

char	**creat_file_mat(t_dlist *tokens, int result, enum e_type type,
		enum e_type typ)
{
	t_dlist	*aux;
	char	**mat;
	int		i;

	i = -1;
	aux = tokens;
	if (result > 0)
	{
		mat = ft_calloc(sizeof(char *), (result + 1));
		aux = go_to_pipe_or_first(aux);
		while (aux)
		{
			if (aux->tok->type == type)
				mat[++i] = ft_strdup(aux->next->tok->lex);
			else if (aux->tok->type == typ && typ == H_DOC)
				mat[++i] = ft_strdup(aux->tok->heredoc_file);
			else if (aux->tok->type == typ && typ == APPEND)
				mat[++i] = ft_strdup(aux->next->tok->lex);
			aux = aux->next;
		}
	}
	else
		mat = NULL;
	return (mat);
}

char	**files_in(t_dlist *tokens)
{
	int		result;
	t_dlist	*aux;
	char	**files;

	aux = tokens;
	result = 0;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == R_IN || aux->tok->type == H_DOC)
			result++;
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	files = creat_file_mat(tokens, result, R_IN, H_DOC);
	return (files);
}

char	**files_out(t_dlist *tokens)
{
	int		result;
	t_dlist	*aux;
	char	**files;

	aux = tokens;
	result = 0;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == R_OUT || aux->tok->type == APPEND)
			result++;
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	files = creat_file_mat(tokens, result, R_OUT, APPEND);
	return (files);
}

char	***have_redirect(t_dlist *tokens)
{
	char	***files;

	files = ft_calloc(sizeof(char **), 4);
	files[0] = files_in(tokens);
	files[1] = files_out(tokens);
	files[2] = have_append(tokens);
	return (files);
}
