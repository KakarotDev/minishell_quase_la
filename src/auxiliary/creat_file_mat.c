/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_file_mat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:11:42 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/21 19:11:53 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**creat_file_mat(t_dlist *tokens, int result, enum e_type type,
		enum e_type typ)
{
	t_dlist	*aux;
	char	**mat;
	int		i;

	i = -1;
	aux = tokens;
	if (result > 0)
	{
		mat = ft_calloc(sizeof(char *), (result + 1));
		aux = go_to_pipe_or_first(aux);
		while (aux)
		{
			if (aux->tok->type == type)
				mat[++i] = ft_strdup(aux->next->tok->lex);
			else if (aux->tok->type == typ && typ == H_DOC)
				mat[++i] = ft_strdup(aux->tok->heredoc_file);
			else if (aux->tok->type == typ && typ == APPEND)
				mat[++i] = ft_strdup(aux->next->tok->lex);
			aux = aux->next;
		}
	}
	else
		mat = NULL;
	return (mat);
}
