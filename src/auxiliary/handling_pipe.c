/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:06:17 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/18 17:20:10 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_pipe(t_dlist **head, char **lexemes, int *index)
{
	long int	metadata[4];

	ft_memset(metadata, 0, sizeof(metadata));
	ft_append_dlist(head, ft_newnode_dlist(lexemes[*index], PIPE, metadata));
	heredoc_file_counter((heredoc_file_counter(-1) + 1));
}
