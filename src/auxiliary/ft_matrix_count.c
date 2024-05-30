/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:44:20 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/13 13:45:03 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_matrix_count(char **matrix)
{
	int	index;

	if (!matrix)
		return (0);
	index = 0;
	while (matrix[index])
		index++;
	return (index);
}
