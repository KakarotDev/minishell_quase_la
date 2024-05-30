/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:43:48 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 20:28:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**hook_environ(char **envp, int free)
{
	static char		**static_envp;

	if (!static_envp && envp)
		static_envp = envp;
	if (static_envp && free)
	{
		ft_free_matrix((void **) static_envp);
		static_envp = NULL;
	}
	return (static_envp);
}
