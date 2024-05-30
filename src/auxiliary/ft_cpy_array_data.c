/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_array_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:46:03 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/09 20:19:56 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_array_data(int *dst, int *src, int size)
{
	int	iter;

	iter = 0;
	if (!src)
		return ;
	while (iter < size)
	{
		dst[iter] = src[iter];
		iter++;
	}
	return ;
}
