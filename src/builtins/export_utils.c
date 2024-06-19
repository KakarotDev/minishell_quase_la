/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:07:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/17 23:21:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	report_error_export(void)
{
	ft_putstr_fd("Error\n export: not a valid identifier\n", 2);
	return (EXIT_FAILURE);
}

void	format_and_print_export(char *variable)
{
	write(1, "declare -x ", 11);
	while (*variable != '=' && *variable)
		variable += write(1, variable, 1);
	if (!*variable)
	{
		write(1, "\n", 1);
		return ;
	}
	else
	{
		variable += write(1, variable, 1);
		write(1, "\"", 1);
	}
	while (*variable)
		variable += write(1, variable, 1);
	write(1, "\"\n", 2);
	return ;
}

int	sorted_print(char **envp, int lenght, unsigned char *boolean_str)
{
	int	var;

	var = -1;
	while (lenght--)
	{
		if (boolean_str[lenght] || !ft_strncmp(envp[lenght], "_=", 2))
			continue ;
		if (var == -1)
			var = lenght;
		else
		{
			if (ft_strcmp(envp[var], envp[lenght]) > 0)
				var = lenght;
		}
	}
	if (var != -1)
	{
		format_and_print_export(envp[var]);
		boolean_str[var]++;
		return (1);
	}
	return (0);
}

int	show_variables(char **envp)
{
	int				array_lenght;
	unsigned char	*boolean_str;

	array_lenght = ft_matrix_count(envp);
	boolean_str = ft_calloc(array_lenght + 1, sizeof(unsigned char));
	while (sorted_print(envp, array_lenght, boolean_str))
		;
	free(boolean_str);
	return (0);
}
