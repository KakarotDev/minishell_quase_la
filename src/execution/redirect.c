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

void	redir_fds_control(t_ast *raiz, t_pipex *p)
{
	if (raiz->files[0] != NULL)
		p->redir_fds[0] = files_in_control(raiz, p);
	else
		p->redir_fds[0] = 0;
	if (raiz->files[1] != NULL)
		p->redir_fds[1] = files_out_control(raiz, p);
	else
		p->redir_fds[1] = 0;
}

char	**creat_file_mat(t_dlist *tokens, int result, enum e_type type,
		enum e_type typ)
{
	t_dlist	*aux_t;
	char	**mat;
	int		i;

	i = -1;
	aux_t = tokens;
	if (result > 0)
	{
		mat = ft_calloc(sizeof(char *), (result + 1));
		aux_t = go_to_pipe_or_first(aux_t);
		while (aux_t)
		{
			if (aux_t->tok->type == type)
				mat[++i] = ft_strdup(aux_t->next->tok->lex);
			else if (aux_t->tok->type == typ && typ == H_DOC)
				mat[++i] = ft_strdup(aux_t->tok->heredoc_file);
			else if (aux_t->tok->type == typ && typ == APPEND)
				mat[++i] = ft_strdup(aux_t->next->tok->lex);
			aux_t = aux_t->next;
		}
	}
	else
		mat = NULL;
	return (mat);
}

char	**files_in(t_dlist *tokens)
{
	int		result;
	t_dlist	*aux_t;
	char	**files;

	aux_t = tokens;
	result = 0;
	while (aux_t->next != NULL)
		aux_t = aux_t->next;
	while (aux_t->tok->type != PIPE && aux_t->prev)
	{
		if (aux_t->tok->type == R_IN || aux_t->tok->type == H_DOC)
			result++;
		aux_t = aux_t->prev;
	}
	if (aux_t->tok->type == R_IN || aux_t->tok->type == H_DOC)
		result++;
	files = creat_file_mat(tokens, result, R_IN, H_DOC);
	return (files);
}

char	**files_out(t_dlist *tokens)
{
	int		result;
	t_dlist	*aux_t;
	char	**files;

	aux_t = tokens;
	result = 0;
	while (aux_t->next != NULL)
		aux_t = aux_t->next;
	while (aux_t->tok->type != PIPE && aux_t->prev != NULL)
	{
		if (aux_t->tok->type == R_OUT || aux_t->tok->type == APPEND)
			result++;
		aux_t = aux_t->prev;
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
