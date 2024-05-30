/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:56:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/17 10:08:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_fd(char *path, int flags)
{
	int	fd;

	fd = 0;
	if (flags == OPEN_WR)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flags == OPEN_RD)
		fd = open(path, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_printf("\n%s\n", path);
		ft_putstr_fd("Error\n An error ocurred when open a file.\n", 2);
	}
	return (fd);
}
