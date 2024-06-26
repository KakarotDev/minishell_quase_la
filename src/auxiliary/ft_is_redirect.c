/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:32:57 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/25 21:17:13 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirect(enum e_type type)
{
	if (type == R_OUT || type == R_IN || type == H_DOC || type == APPEND)
		return (TRUE);
	return (FALSE);
}
