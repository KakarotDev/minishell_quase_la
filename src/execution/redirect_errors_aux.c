/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:06:40 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 20:07:07 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	converse_index(char **matrix_err, int result)
{
	int	index;

	index = result;
	index -= ft_atoi(matrix_err[2]);
	free(matrix_err[2]);
	matrix_err[2] = ft_itoa(index);
}
