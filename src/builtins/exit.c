/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:24 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/21 18:59:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validating_string(const char *arg)
{
	int	index;

	index = 0;
	while (arg[index])
	{
		if (!ft_isdigit(arg[index]))
		{
			if (index == 0 && arg[index] != '\0'
				&& (arg[index] == '-' || arg[index] == '+'))
			{
				index++;
				continue ;
			}
			else if (!ft_isdigit(arg[index]))
				return (TRUE);
		}
		index++;
	}
	return (FALSE);
}

int	validating_values_64bits(const char *arg, const char *value)
{
	int	index;

	index = 0;
	while (arg[index])
	{
		if (biggest_character(arg[index], value[index]))
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	validating_arg(const char *arg)
{
	int	string_lenght;
	int	maximum_string_lenght;
	int	is_negative;
	int	has_math_symbol;

	if (validating_string(arg))
		return (EXIT_FAILURE);
	verifying_math_symbol(arg, &is_negative, &has_math_symbol);
	string_lenght = ft_strlen(arg);
	if (has_math_symbol)
		maximum_string_lenght = ft_strlen(MAX64BITS);
	else
		maximum_string_lenght = ft_strlen(&MAX64BITS[1]);
	if (string_lenght > maximum_string_lenght)
		return (EXIT_FAILURE);
	if (string_lenght == maximum_string_lenght)
	{
		if (is_negative)
			return (validating_values_64bits(arg, MIN64BITS));
		else if (has_math_symbol)
			return (validating_values_64bits(arg, MAX64BITS));
		else
			validating_values_64bits(arg, &MAX64BITS[1]);
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_ast *root, int *std_fds)
{
	char			**cmd_matrix;
	long long int	exit_value;

	cmd_matrix = root->cmd_matrix;
	if (cmd_matrix[1])
	{
		if (validating_arg(cmd_matrix[1]))
			return (write_err_msg_exit(NUMARGREQUIRED, cmd_matrix[1]));
		if (cmd_matrix[2])
			exit (write_err_msg_exit(TOOMANYARG, NULL));
		exit_value = ft_atolli(cmd_matrix[1]);
		finishing_program_exit(root, std_fds, exit_value);
	}
	else
		finishing_program_exit(root, std_fds, last_exit_status(-1));
	return (EXIT_FAILURE);
}
