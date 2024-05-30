/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:10 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 20:07:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_echo(char *str, int *space)
{
	if (*space && *str != '\0')
		write(1, " ", 1);
	else
		*space += 1;
	while (*str)
		str += write(1, str, 1);
	return ;
}

int	echo(char **matrix)
{
	int	nl;
	int	space;
	int	i;

	nl = 1;
	space = 0;
	i = 0;
	if (!matrix[++i])
		return (write(1, "\n", 1) - 1);
	if (!ft_strncmp(matrix[i], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while (matrix[i])
	{
		write_echo(matrix[i], &space);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
