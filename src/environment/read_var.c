/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:40:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/09 18:24:58 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_var(char **environment, char *var)
{
	char	*varname;

	if (!ft_isalpha(*var))
		return (ft_strdup(""));
	varname = ft_strjoin(var, "=");
	while (*environment)
	{
		if (!ft_strncmp(*environment, varname, ft_strlen(varname)))
		{
			free(varname);
			return (ft_strdup(*environment));
		}
		environment++;
	}
	free(varname);
	return (ft_strdup(""));
}
