/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:54:21 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 10:54:21 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_isspace(char *input, int fd)
{
	if (input == NULL)
		return (input);
	while (*input == ' ' || *input == '\t')
		input++;
	write(fd, "\n", 1);
	return (input);
}
