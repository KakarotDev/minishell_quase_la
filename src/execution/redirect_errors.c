/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:59:55 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/24 20:59:55 by parthur-         ###   ########.fr       */
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

void	ambiguous_redirect_validation(char **matrix_err,
		t_dlist *tok, int result, int std)
{
	if (tok->next->tok->type == WORD)
	{
		if (matrix_err[0])
			format_error(matrix_err, tok, result, std);
		else
			format_error(matrix_err, tok, result, std);
	}
	else if (tok->next->next)
	{
		if (tok->next->next->tok->type == IO_FILE)
		{
			if (matrix_err[0])
				format_error(matrix_err, tok, result, std);
			else
				format_error(matrix_err, tok, result, std);
		}
	}
}

void	format_error(char **matrix_err, t_dlist *tok, int result, int std)
{
	if (matrix_err[0])
	{
		free(matrix_err[0]);
		free(matrix_err[1]);
		matrix_err[0] = format_string("(",
				((char *) tok->next->tok->metadata[3]),
				"): ", "ambiguous redirect\n");
		matrix_err[1] = ft_itoa(std + 1);
		matrix_err[2] = ft_itoa(result);
	}
	else
	{
		matrix_err[0] = format_string("(",
				((char *) tok->next->tok->metadata[3]), "): ",
				"ambiguous redirect\n");
		matrix_err[1] = ft_itoa(std + 1);
		matrix_err[2] = ft_itoa(result);
	}
}

int	redirect_in_error(char **matrix_err, char *file, int index)
{
	if ((ft_atoi(matrix_err[1]) + 1) == 2 && ft_atoi(matrix_err[2]) == index)
	{
		ft_putstr_fd(matrix_err[0], STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (access(file, F_OK) == -1)
	{
		write_err_msg(file, NOFILE);
		return (EXIT_FAILURE);
	}
	else if (access(file, R_OK) == -1)
	{
		write_err_msg(file, MINI_EACCES);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redirect_out_error(char **matrix_err, char *file, int index)
{
	int	fd;

	if ((ft_atoi(matrix_err[1]) + 1) == 3 && ft_atoi(matrix_err[2]) == index)
	{
		ft_putstr_fd(matrix_err[0], STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
	{
		write_err_msg(file, MINI_EISDIR);
		close(fd);
		return (EXIT_FAILURE);
	}
	else if ((access(file, W_OK) != 0))
	{
		write_err_msg(file, MINI_EACCES);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
