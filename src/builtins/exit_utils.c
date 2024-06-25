/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:55:12 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/21 19:00:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atolli(const char *nptr)
{
	long long int	signal;
	long long int	result;

	signal = 1;
	result = 0;
	if (!nptr)
		return (0);
	while (((*nptr >= '\t') && (*nptr <= '\r')) || *nptr == ' ')
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	return (result * signal);
}

int	biggest_character(char character, char comparator)
{
	if (character > comparator)
		return (TRUE);
	return (FALSE);
}

int	finishing_program_exit(t_ast *root, int *std_fds,
		long long int exit_status)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	hook_environ(NULL, 1);
	hook_pwd(NULL, 1);
	ft_free_ast(root);
	close(*std_fds);
	exit (exit_status & 0xFF);
}

int	write_err_msg_exit(enum e_error error, const char *arg)
{
	char	*str_error;

	str_error = "";
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (error == NUMARGREQUIRED)
		str_error = format_string("exit: ", (char *) arg,
				": numeric argument required\n", "");
	else if (error == TOOMANYARG)
		str_error = ft_strdup("exit: too many arguments\n");
	ft_putstr_fd(str_error, STDERR_FILENO);
	free(str_error);
	if (error == NUMARGREQUIRED)
		return (last_exit_status(2));
	return (last_exit_status(1));
}

void	verifying_math_symbol(const char *arg,
		int *is_negative, int *has_math_symbol)
{
	*has_math_symbol = 0;
	if (*arg == '-' || *arg == '+')
	{
		*has_math_symbol = 1;
		*is_negative = 0;
		if (*arg == '-')
			*is_negative = 1;
	}
	return ;
}
