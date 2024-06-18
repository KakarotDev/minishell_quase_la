/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:02:51 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/18 15:42:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	aux_path_validation(char *path)
//{
//	int	ret;
//	int	fd;
//
//	if (path == NULL)
//		return (EXIT_SUCCESS);
//	ret = access(path, F_OK);
//	if (ret < 0)
//	{
//		write_err_msg(path, NOFILE);
//		return (last_exit_status(EXIT_FAILURE));
//	}
//	fd = open(path, __O_DIRECTORY);
//	if (fd > 0)
//	{
//		write_err_msg(path, MINI_EISDIR);
//		close(fd);
//		return (last_exit_status(EXIT_FAILURE));
//	}
//	ret = access(path, X_OK);
//	if (ret < 0)
//	{
//		write_err_msg(path, MINI_EACCES);
//		return (last_exit_status(EXIT_FAILURE));
//	}	
//	return (EXIT_SUCCESS);
//}

char	**partial_path_mat_creator(char *path)
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

int	checking_the_path_except_the_last_one(char *path)
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
		{
			write_err_msg(path, NOFILE);
			close(dir_fd);
			return (last_exit_status(EXIT_FAILURE));
		}
		if (access(mat_partial_paths[i], X_OK) < 0)
		{
			write_err_msg(path, MINI_EACCES);
			return (last_exit_status(EXIT_FAILURE));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	checking_the_last_one(char *path)
{
	int	dir_fd;

	dir_fd = open(path, __O_DIRECTORY);
	if (dir_fd > 0)
	{
		write_err_msg(path, MINI_EISDIR);
		close(dir_fd);
		return (last_exit_status(EXIT_FAILURE));
	}
	else
	{
		if (access(path, F_OK) < 0)
		{
			write_err_msg(path, NOFILE);
			return (last_exit_status(EXIT_FAILURE));
		}
		else if (access(path, X_OK) < 0)
		{
			write_err_msg(path, MINI_EACCES);
			return (last_exit_status(EXIT_FAILURE));
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
