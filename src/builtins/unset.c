/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:00:01 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:06:23 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_varname_valid(const char *variable, char **environ)
{
	int		i;
	char	*temp;

	if (!variable)
		return (0);
	i = 0;
	while (environ[i])
	{
		if (ft_have_char(environ[i], '='))
		{
			temp = ft_strjoin(variable, "=");
			if (!ft_strncmp(environ[i], temp, ft_strlen(temp)))
			{
				free(temp);
				return (TRUE);
			}
			free(temp);
		}
		else
			if (!ft_strncmp(environ[i], variable, ft_strlen(environ[i])))
				return (TRUE);
		i++;
	}
	return (FALSE);
}

int	check_with_assignment(const char *variable, char *curr_variable)
{
	char	*varname;
	int		boolean;

	if (!*variable)
		return (FALSE);
	varname = ft_strjoin(variable, "=");
	boolean = FALSE;
	if (!ft_strncmp(curr_variable, varname, ft_strlen(varname)))
		boolean = TRUE;
	free(varname);
	return (boolean);
}

void	remaking_env_unset(const char *variable, char **environ)
{
	char	**new_environ;
	int		i;
	int		j;

	new_environ = ft_calloc(ft_matrix_count(environ), sizeof(char *));
	i = -1;
	j = 0;
	while (environ[++i])
	{
		if (ft_have_char(environ[i], '='))
		{
			if (!check_with_assignment(variable, environ[i]))
				new_environ[j++] = ft_strdup(environ[i]);
		}
		else
		{
			if (ft_strcmp(environ[i], variable))
				new_environ[j++] = ft_strdup(environ[i]);
		}
	}
	hook_environ(NULL, 1);
	hook_environ(new_environ, 0);
	return ;
}

int	unset(char **args)
{
	char	**environ;
	int		i;

	i = 0;
	environ = hook_environ(NULL, 0);
	while (args[++i])
	{
		if (!is_varname_valid(args[i], environ))
			continue ;
		else
		{
			remaking_env_unset(args[i], environ);
			environ = hook_environ(NULL, 0);
		}
	}
	return (EXIT_SUCCESS);
}
