/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entrance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:10:39 by myokogaw          #+#    #+#             */
/*   Updated: 2024/05/14 15:17:11 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_entrance(void)
{
	char	*entrance;
	char	*mid;

	mid = ft_strjoin("minishell:", hook_pwd(NULL, 0));
	entrance = ft_strjoin(mid, "$ ");
	free(mid);
	return (entrance);
}
