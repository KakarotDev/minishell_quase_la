/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:02:51 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/26 19:36:11 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**partial_path_mat_creator(char *path)
{
	int		i;
	int		mat_len;
	int		i_mat;
	char	**mat;

	i = -1;
	i_mat = 0;
	mat_len = 0;
	while (path[++i] != '\0')
	{
		if (path[i] == '/')
			mat_len++;
	}
	mat = (char **)ft_calloc(sizeof(char *), (mat_len + 2));
	i = -1;
	while (path[++i] != '\0')
	{
		if (path[i + 1] == '/' || path[i + 1] == '\0')
		{
			mat[i_mat] = ft_strndup(path, 0, (i + 1));
			i_mat++;
		}
	}
	return (mat);
}

static int	close_and_return(char *path, char **mat_partial_paths, int control)
{
	if (control == 0)
	{
		write_err_msg_status(path, NOFILE, 127);
		ft_free_matrix((void **)mat_partial_paths);
		return (EXIT_FAILURE);
	}
	else if (control == 1)
	{
		write_err_msg_status(path, MINI_EACCES, 126);
		ft_free_matrix((void **)mat_partial_paths);
		return (EXIT_FAILURE);
	}
	return (0);
}

static int	checking_the_path_except_the_last_one(char *path)
{
	char	**mat_partial_paths;
	int		dir_fd;
	int		i;

	i = 0;
	mat_partial_paths = NULL;
	mat_partial_paths = partial_path_mat_creator(path);
	while (mat_partial_paths[i + 1])
	{
		dir_fd = open(mat_partial_paths[i], __O_DIRECTORY);
		if (dir_fd < 0)
			return (close_and_return(path, mat_partial_paths, 0));
		close(dir_fd);
		if (access(mat_partial_paths[i], X_OK) < 0)
			return (close_and_return(path, mat_partial_paths, 1));
		i++;
	}
	ft_free_matrix((void **)mat_partial_paths);
	return (EXIT_SUCCESS);
}

static int	checking_the_last_one(char *path)
{
	int	dir_fd;

	dir_fd = open(path, __O_DIRECTORY);
	if (dir_fd > 0)
	{
		write_err_msg_status(path, MINI_EISDIR, 126);
		close(dir_fd);
		return (EXIT_FAILURE);
	}
	else
	{
		if (access(path, F_OK) < 0)
		{
			write_err_msg_status(path, NOFILE, 127);
			return (EXIT_FAILURE);
		}
		else if (access(path, X_OK) < 0)
		{
			write_err_msg_status(path, MINI_EACCES, 126);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	path_validation(char *path, char **matrix)
{
	if (path)
	{
		if (checking_the_path_except_the_last_one(path) == 1)
			return (EXIT_FAILURE);
		if (checking_the_last_one(path) == 1)
			return (EXIT_FAILURE);
	}
	if (path == NULL)
	{
		ft_putstr_fd(matrix[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (last_exit_status(127));
	}
	return (EXIT_SUCCESS);
}
