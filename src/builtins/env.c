/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:58:34 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/07 20:19:16 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **args)
{
	char	**envp;
	int		size;

	size = 1;
	envp = hook_environ(NULL, 0);
	while (*(++args))
		size++;
	if (size > 1)
	{
		ft_putstr_fd("Error\n env: doesn't accept option or arguments\n", 2);
		return (EXIT_FAILURE);
	}
	while (*envp)
	{
		if (*envp && ft_strchr(*envp, '=') && ft_strncmp(*envp, "_=", 2))
			printf("%s\n", *envp);
		envp++;
	}
	return (EXIT_SUCCESS);
}
