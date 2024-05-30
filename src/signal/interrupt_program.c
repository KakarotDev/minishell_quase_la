/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt_program.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:53:36 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/29 22:53:36 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interrupt_program(char *input)
{
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	write(1, "\n", 1);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free(input);
	rl_clear_history();
	return (0);
}
