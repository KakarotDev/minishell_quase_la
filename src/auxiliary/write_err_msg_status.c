/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_err_msg_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:19:49 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/21 18:21:22 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_err_msg_status(char	*file, enum e_error error, int status_err)
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
	last_exit_status(status_err);
}
