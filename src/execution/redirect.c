/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:00:21 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/24 21:00:21 by parthur-         ###   ########.fr       */
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

char	***have_redirect(t_dlist *tokens)
{
	char	***files;

	files = (char ***) ft_calloc(sizeof(char **), 5);
	files[3] = (char **) ft_calloc(sizeof(char *), 4);
	files[0] = files_in(tokens, files[3]);
	files[1] = files_out(tokens, files[3]);
	files[2] = have_append(tokens);
	return (files);
}
