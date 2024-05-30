/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_varname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:27:53 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/10 10:27:53 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*validating_varname(char *varname, int *is_quoted)
{
	if (*is_quoted)
	{
		if (!ft_isalnum(*varname) && *varname != '_' && *varname != '?')
		{
			free(varname);
			varname = NULL;
			return (varname);
		}
	}
	else if (!*varname || *varname == ' ')
	{
		free(varname);
		varname = NULL;
	}
	return (varname);
}
