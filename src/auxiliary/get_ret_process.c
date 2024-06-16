/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ret_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:47:11 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:07:01 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ret_process(int pid)
{
	int	status;

	status = -1;
	waitpid(pid, &status, 0);
	if (status == (128 + SIGQUIT))
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
