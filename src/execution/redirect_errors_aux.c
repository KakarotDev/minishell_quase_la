/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:06:40 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/21 19:09:36 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_err_msg(char	*file, enum e_error error)
{
	char	*str_error;

	str_error = "";
	if (error == MINI_EISDIR)
		str_error = "Is a directory\n";
	else if (error == MINI_EACCES)
		str_error = "Permission denied\n";
	else if (error == NOFILE)
		str_error = "No such file or directory\n";
	str_error = format_string("(", file, "): ", str_error);
	ft_putstr_fd(str_error, STDERR_FILENO);
	free(str_error);
	last_exit_status(EXIT_FAILURE);
}

void	closing_process_message(t_ast *root, int index_files,
	int *index, enum e_error error)
{
	write_err_msg(root->files[index_files][*index], error);
	*index = -2;
}

void	setting_redirect_error(int *index, enum e_error error, int fd)
{
	if (fd > 0)
		close(fd);
	*index = -2;
	last_exit_status(error);
}

void	converse_index(char **matrix_err, int result)
{
	int	index;

	index = result;
	index -= ft_atoi(matrix_err[2]);
	free(matrix_err[2]);
	matrix_err[2] = ft_itoa(index);
}
