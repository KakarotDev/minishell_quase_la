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

char	*format_string(char *s, char *s1, char *s2, char *s3)
{
	int		lenght;
	int		index;
	char	*formatted_string;

	lenght = (ft_strlen(s) + ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	formatted_string = ft_calloc(lenght + 1, sizeof(char));
	formatted_string[lenght] = '\0';
	lenght = 0;
	index = 0;
	while (s[index])
		formatted_string[lenght++] = s[index++];
	index = 0;
	while (s1[index])
		formatted_string[lenght++] = s1[index++];
	index = 0;
	while (s2[index])
		formatted_string[lenght++] = s2[index++];
	index = 0;
	while (s3[index])
		formatted_string[lenght++] = s3[index++];
	return (formatted_string);
}

void	write_err_msg(char	*file, enum e_error error, int status_error)
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
	last_exit_status(status_error);
}

void	closing_process_message(t_ast *root, int index_files,
		int *index, enum e_error error)
{
	write_err_msg(root->files[index_files][*index], error, 1);
	*index = -2;
}

void	setting_redirect_error(int *index, enum e_error error, int fd)
{
	if (fd > 0)
		close(fd);
	*index = -2;
	last_exit_status(error);
}

int	redirect_in_error(t_ast *root)
{
	int	index;

	index = 0;
	while (index != -1 && root->files[0][index] != NULL)
	{
		if (ft_atoi(root->files[3][1]) == 0
			&& ft_atoi(root->files[3][2]) == index)
		{
			ft_putstr_fd(root->files[3][0], STDERR_FILENO);
			index = -2;
		}
		if (index != -2 && access(root->files[0][index], F_OK) == -1)
			closing_process_message(root, 0, &index, NOFILE);
		else if (index != -2 && access(root->files[0][index], R_OK) == -1)
			closing_process_message(root, 0, &index, MINI_EACCES);
		index++;
	}
	if (index == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// void	redirect_out_error_aux(int fd, int index, t_ast *root)
// {
// 	if (fd != -1)
// 	{
// 		closing_process_message(root, 1, &index, MINI_EISDIR);
// 		close(fd);
// 	}
// 	else if ((access(root->files[1][index], W_OK) != 0))
// 		closing_process_message(root, 1, &index, MINI_EACCES);
// }

int	redirect_out_error(t_ast *root)
{
	int	index;
	int	fd;

	index = 0;
	while (index != -1 && root->files[1][index] != NULL)
	{
		if (ft_atoi(root->files[3][1]) == 1
			&& ft_atoi(root->files[3][2]) == index)
		{
			ft_putstr_fd(root->files[3][0], STDERR_FILENO);
			index = -2;
		}
		if (index != -2)
		{
			fd = open(root->files[1][index], __O_DIRECTORY);
			if (fd != -1)
			{
				closing_process_message(root, 1, &index, MINI_EISDIR);
				close(fd);
			}
			else if ((access(root->files[1][index], W_OK) != 0))
				closing_process_message(root, 1, &index, MINI_EACCES);
			//redirect_out_error_aux(fd, index, root);
		}
		index++;
	}
	if (index == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
