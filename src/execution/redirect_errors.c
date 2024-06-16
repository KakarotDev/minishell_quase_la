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

void	write_err_msg_redirect(char	*file, enum e_error error)
{
	char	*str_error;

	if (error == MINI_EISDIR)
		str_error = strerror(MINI_EISDIR);
	else if (error == MINI_EACCES)
		str_error = strerror(MINI_EACCES);
	else if (error == NOFILE)
		str_error = "No such file or directory\n";
	ft_putstr_fd("(", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("): ", STDERR_FILENO);
	ft_putstr_fd(str_error, STDERR_FILENO);
	last_exit_status(1);
}

// void	printf_message(t_ast *raiz, int i, int type)
// {
// 	if (type == 1)
// 		printf("No such file or directory: %s\n", raiz->files[0][i]);
// 	if (type == 2)
// 		printf("unreadable_file: Permission denied %s\n", raiz->files[0][i]);
// 	if (type == 3)	
// 		printf("unwritable_file: Permission denied %s\n", raiz->files[1][i]);
// }

void	closing_process_message(t_ast *root, int *index, enum e_error error)
{
	write_err_msg_redirect(root->files[1][*index], error);
	if (root->redir_fds[0] != 0)
		close(root->redir_fds[0]);
	if (root->redir_fds[1] != 0)
		close(root->redir_fds[1]);
	ft_free_ast(root); 
	if (is_process(-1))
	{
		close(STDIN_FILENO);
		close(STDERR_FILENO);
		close(STDOUT_FILENO);
		hook_environ(NULL, 1);
		hook_pwd(NULL, 1);
		exit (1);
	}
	root = NULL;
	*index = -2;
}

void	redirect_in_error(t_ast *root)
{
	int	index;

	index = 0;
	while (index != -1 && root->files[0][index] != NULL)
	{
		if (access(root->files[0][index], F_OK) == -1)
			closing_process_message(root, &index, NOFILE);
		else if (access(root->files[0][index], R_OK) == -1)
			closing_process_message(root, &index, MINI_EACCES);
		index++;
	}
}

void	redirect_out_error(t_ast *root)
{
	int	index;
	int	fd;

	index = 0;
	while (index != -1 && root->files[1][index] != NULL)
	{
		fd = open(root->files[1][index], __O_DIRECTORY);
		if (fd != -1)
		{
			closing_process_message(root, &index, MINI_EISDIR);
			close(fd);
		}
		else if ((access(root->files[1][index], W_OK) != 0))
			closing_process_message(root, &index, MINI_EACCES);
		index++;
	}
}
