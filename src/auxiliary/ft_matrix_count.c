/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:44:20 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:11:20 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
