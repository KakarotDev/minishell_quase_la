/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:02:51 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/17 02:53:55 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aux_path_validation(char *path)
{
	int	ret;
	int	fd;

	if (path == NULL)
		return (EXIT_SUCCESS);
	ret = access(path, F_OK);
	if (ret < 0)
	{
		write_err_msg(path, NOFILE);
		return (last_exit_status(EXIT_FAILURE));
	}
	fd = open(path, __O_DIRECTORY);
	if (fd > 0)
	{
		write_err_msg(path, MINI_EISDIR);
		close(fd);
		return (last_exit_status(EXIT_FAILURE));
	}
	ret = access(path, X_OK);
	if (ret < 0)
	{
		write_err_msg(path, MINI_EACCES);
		return (last_exit_status(EXIT_FAILURE));
	}	
	return (EXIT_SUCCESS);
}

char	**partial_path_mat_creator(char *path)
{
	int		len;
	int		i;
	int		mat_len;
	int		i_mat;
	char	**mat;

	i = 0;
	i_mat = 0;
	len = ft_strlen(path);
	mat_len = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			mat_len++;
		i++;
	}
	mat = (char **)ft_calloc(sizeof(char *), (mat_len + 2));
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i + 1] == '/' || path[i + 1] == '\0')
		{
			mat[i_mat] = ft_strndup(path, 0, (i + 1));
			i_mat++;
		}
		i++;
	}
	i = 0;
	while (mat[i] != NULL)
	{
		printf("%s\n", mat[i]);
		i++;
	}
	printf("\n");
	return (mat);
}

int	path_validation(char *path, char **matrix)
{
	char	**mat_partial_paths;
	int		i;
	int		dir_fd;
	int		ret_access_exec;
	int		ret_access_file;

	i = 0;
	dir_fd = 0;
	ret_access_exec = 0;
	ret_access_file = 0;
	mat_partial_paths = NULL;
	if (path)
	{
		mat_partial_paths = partial_path_mat_creator(path);
		while (mat_partial_paths[i + 1])
		{
			dir_fd = open(mat_partial_paths[i], __O_DIRECTORY);
			if (dir_fd > 0)
			{
				write_err_msg(path, NOFILE);
				close(dir_fd);
				return (last_exit_status(EXIT_FAILURE));
			}
			ret_access_exec = access(mat_partial_paths[i], X_OK);
			if (ret_access_exec < 0)
			{
				write_err_msg(path, MINI_EACCES);
				return (last_exit_status(EXIT_FAILURE));
			}
			i++;
		}
		i++;
		dir_fd = open(path, __O_DIRECTORY);
		if (dir_fd > 0)
		{
			write_err_msg(path, MINI_EISDIR);
			close(dir_fd);
			return (last_exit_status(EXIT_FAILURE));
		}
		else
		{
			ret_access_file = access(path, F_OK);
			if (ret_access_file < 0)
			{
				write_err_msg(path, NOFILE);
				return (last_exit_status(EXIT_FAILURE));
			}
		}
		printf("\n");
	}
	// if (aux_path_validation(path))
	// 	return (EXIT_FAILURE);
	if (path == NULL)
	{
		ft_putstr_fd(matrix[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (last_exit_status(127));
	}
	return (EXIT_SUCCESS);
}
