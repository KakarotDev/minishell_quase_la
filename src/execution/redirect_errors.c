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
		str_error = "Is a directory\n";
	else if (error == MINI_EACCES)
		str_error = "Permission denied\n";
	else if (error == NOFILE)
		str_error = "No such file or directory\n";
	ft_putstr_fd("(", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("): ", STDERR_FILENO);
	ft_putstr_fd(str_error, STDERR_FILENO);
	last_exit_status(EXIT_FAILURE);
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

void	closing_process_message(t_ast *root, int index_files, int *index, enum e_error error)
{
	write_err_msg_redirect(root->files[index_files][*index], error);
	if (root->redir_fds[0] != 0 && root->redir_fds[0] != -1)
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
		exit(last_exit_status(-1));
	}
	root = NULL;
	*index = -2;
}

int	redirect_in_error(t_ast *root)
{
	int	index;

	index = 0;
	while (index != -1 && root->files[0][index] != NULL)
	{
		if (access(root->files[0][index], F_OK) == -1)
			closing_process_message(root, 0, &index, NOFILE);
		else if (access(root->files[0][index], R_OK) == -1)
			closing_process_message(root, 0, &index, MINI_EACCES);
		index++;
	}
	if (index == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redirect_out_error(t_ast *root)
{
	int	index;
	int	fd;

	index = 0;
	while (index != -1 && root->files[1][index] != NULL)
	{
		fd = open(root->files[1][index], __O_DIRECTORY);
		if (fd != -1)
		{
			closing_process_message(root, 1, &index, MINI_EISDIR);
			close(fd);
		}
		else if ((access(root->files[1][index], W_OK) != 0))
			closing_process_message(root, 1, &index, MINI_EACCES);
		index++;
	}
	if (index == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
