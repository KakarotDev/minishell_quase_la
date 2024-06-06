/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:15 by marvin            #+#    #+#             */
/*   Updated: 2024/05/30 16:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_message(t_ast *raiz, int i, int type)
{
	if (type == 1)
		printf("No such file or directory: %s\n", raiz->files[0][i]);
	if (type == 2)
		printf("unreadable_file: Permission denied %s\n", raiz->files[0][i]);
	if (type == 3)
		printf("unwritable_file: Permission denied %s\n", raiz->files[1][i]);
}

void	closing_process_message(t_ast *raiz, t_pipex *p, int i, int type)
{
	printf_message(raiz, i, type);
	if (p->pipe_fd[1])
		close_fds(1024);
	else
		close_fds(1024);
	ft_free_matrix_char(p->paths.mat_path);
	free(p);
	ft_free_ast(raiz->first);
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	exit(0);
}

void	redirect_in_error(t_ast *raiz, t_pipex *p)
{
	int	i;

	i = 0;
	while (raiz->files[0][i] != NULL)
	{
		if (access(raiz->files[0][i], F_OK) != 0)
			closing_process_message(raiz, p, i, 1);
		if (access(raiz->files[0][i], R_OK) != 0)
			closing_process_message(raiz, p, i, 2);
		i++;
	}
}

void	redirect_out_error(t_ast *raiz, t_pipex *p)
{
	int	i;

	i = 0;
	while (raiz->files[1][i] != NULL)
	{
		if (access(raiz->files[1][i], W_OK) != 0)
			closing_process_message(raiz, p, i, 3);
		i++;
	}
}
