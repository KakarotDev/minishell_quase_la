/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:04:27 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/21 19:26:27 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	files_in_control(t_ast *root)
{
	int	i;

	i = 0;
	while (root->files[0][i] != NULL)
	{
		if (redirect_in_error(root->files[3], root->files[0][i], i))
			return (EXIT_FAILURE);
		if (root->redir_fds[0] != 0)
			close(root->redir_fds[0]);
		root->redir_fds[0] = open(root->files[0][i], O_RDONLY);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**files_in(t_dlist *tokens, char **matrix_err)
{
	int		result;
	char	**files;
	t_dlist	*aux;

	aux = tokens;
	result = 0;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == R_IN || aux->tok->type == H_DOC)
			ambiguous_redirect_validation(matrix_err, aux, ++result, 0);
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	if (matrix_err[0])
		converse_index(matrix_err, result);
	files = creat_file_mat(tokens, result, R_IN, H_DOC);
	return (files);
}
