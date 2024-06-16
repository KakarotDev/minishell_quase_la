/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:32:57 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:10:56 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirect(enum e_type type)
{
	if (type == R_OUT || type == R_IN || type == H_DOC || type == APPEND)
		return (TRUE);
	return (FALSE);
}
