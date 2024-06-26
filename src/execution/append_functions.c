/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:03:37 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/26 19:37:05 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_append(char **mat_append, char *ref)
{
	int	i;

	i = 0;
	while (mat_append[i])
	{
		if (ft_strcmp(mat_append[i], ref) == 0)
		{
			free(ref);
			return (1);
		}	
		i++;
	}
	free(ref);
	return (0);
}

static char	**creat_append_mat(t_dlist *aux_t, int size_append)
{
	int		i;
	char	**appends;
	int		i_append;

	i_append = 0;
	i = 0;
	appends = ft_calloc(sizeof(char *), (size_append + 1));
	while (aux_t->next != NULL)
	{
		if (aux_t->tok->type == R_OUT || aux_t->tok->type == APPEND)
			i++;
		if (aux_t->tok->type == APPEND)
		{
			appends[i_append] = ft_itoa(i - 1);
			i_append++;
		}
		aux_t = aux_t->next;
	}
	return (appends);
}

char	**have_append(t_dlist *tokens)
{
	int		i;
	t_dlist	*aux_t;
	char	**appends;

	i = 0;
	aux_t = tokens;
	appends = NULL;
	while (aux_t->next != NULL)
		aux_t = aux_t->next;
	while (aux_t->tok->type != PIPE && aux_t->prev != NULL)
	{
		if (aux_t->tok->type == APPEND)
			i++;
		aux_t = aux_t->prev;
	}
	if (i > 0)
		appends = creat_append_mat(aux_t, i);
	return (appends);
}
