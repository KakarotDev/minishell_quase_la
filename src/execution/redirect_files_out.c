/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:04:07 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 20:43:19 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	files_out_control(t_ast *root)
{
	int	i;

	i = 0;
	while (root && root->files[1][i] != NULL)
	{
		if (root->redir_fds[1] != 0)
			close(root->redir_fds[1]);
		if (root->files[2] != NULL)
		{
			if (check_append(root->files[2], ft_itoa(i)) > 0)
				root->redir_fds[1] = open(root->files[1][i],
						O_WRONLY | O_CREAT | O_APPEND, 0000666);
			else
				root->redir_fds[1] = open(root->files[1][i],
						O_WRONLY | O_CREAT | O_TRUNC, 0000666);
		}
		else
			root->redir_fds[1] = open(root->files[1][i],
					O_WRONLY | O_CREAT | O_TRUNC, 0000666);
		if (redirect_out_error(root->files[3], root->files[1][i], i))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**files_out(t_dlist *tokens, char **matrix_err)
{
	int		result;
	char	**files;
	t_dlist	*aux;

	aux = tokens;
	result = 0;
	if (matrix_err[0] != NULL)
		return (NULL);
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == R_OUT || aux->tok->type == APPEND)
			ambiguous_redirect_validation(matrix_err, aux, ++result, 1);
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	if (matrix_err[0])
		converse_index(matrix_err, result);
	files = creat_file_mat(tokens, result, R_OUT, APPEND);
	return (files);
}
