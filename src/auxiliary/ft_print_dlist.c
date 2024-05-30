/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:41:51 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/30 02:41:51 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_dlist(t_dlist **head)
{
	t_dlist	*temp;

	if (!head)
		return ;
	if (!*head)
		return ;
	temp = *head;
	while (temp)
	{
		if (temp->tok->lex)
			printf("%s\n", temp->tok->lex);
		if (temp->tok->type == 1)
			printf("%s\n", "DGREAT");
		else if (temp->tok->type == 2)
			printf("%s\n", "DLESS");
		else if (temp->tok->type == 3)
			printf("%s\n", "PIPE");
		else if (temp->tok->type == 4)
			printf("%s\n", "R_OUT");
		else if (temp->tok->type == 5)
			printf("%s\n", "R_IN");
		else if (temp->tok->type == 6)
			printf("%s\n", "WORD");
		else if (temp->tok->type == 7)
			printf("%s\n", "ASSIGNMENT_WORD");
		if (temp->next == NULL)
			break ;
		printf("\n");
		temp = temp->next;
	}
	return ;
}
