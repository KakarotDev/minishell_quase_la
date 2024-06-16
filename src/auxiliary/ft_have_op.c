/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_have_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:12:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/04/09 11:12:55 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_have_op(char *input)
{
	if (!ft_strncmp(input, "<<", 2)
		|| !ft_strncmp(input, ">>", 2))
		return (TRUE);
	else if (!ft_strncmp(input, "<", 1)
		|| !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "|", 1))
		return (TRUE);
	return (FALSE);
}
