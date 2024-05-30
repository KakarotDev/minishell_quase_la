/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:17:51 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/26 19:17:51 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

char	**copy_environ(void)
{
	char	**my_environ;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	my_environ = (char **) ft_calloc(i + 1, sizeof(char *));
	if (!my_environ)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		my_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	return (my_environ);
}
