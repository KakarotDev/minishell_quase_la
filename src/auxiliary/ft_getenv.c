/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:15:31 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 11:15:31 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *varname)
{
	char	*varname_and_value;
	char	*value;

	varname_and_value = read_var(hook_environ(NULL, 0), varname);
	value = getting_content(varname_and_value);
	free(varname_and_value);
	if (!*value)
	{
		free(value);
		return (NULL);
	}
	return (value);
}
