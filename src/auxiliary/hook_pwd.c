/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:58:57 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/05 17:09:47 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hook_pwd(char *n_pwd, int to_free)
{
	static char	*static_pwd;

	if (!static_pwd && n_pwd)
		static_pwd = n_pwd;
	if (static_pwd && to_free)
	{
		free(static_pwd);
		static_pwd = NULL;
	}
	return (static_pwd);
}
