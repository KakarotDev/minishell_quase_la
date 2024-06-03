/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:09:03 by parthur-          #+#    #+#             */
/*   Updated: 2024/06/03 19:13:35 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_paths(t_pipex *p)
{
	int		i;
	char	*temp;
	char	**envp;

	i = 0;
	envp = hook_environ(NULL, 0);
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	p->paths.init_path = ft_strdup(envp[i] + 5);
	i = 0;
	p->paths.mat_path = ft_split(p->paths.init_path, ':');
	free(p->paths.init_path);
	p->paths.mat_len = matrix_len(p->paths.mat_path);
	while (i < p->paths.mat_len)
	{
		temp = ft_strjoin(p->paths.mat_path[i], "/");
		free(p->paths.mat_path[i]);
		p->paths.mat_path[i] = temp;
		i++;
	}
}

char	*cria_path(t_dlist *tokens, t_pipex *p)
{
	t_dlist	*aux_t;
	int		i;
	char	*path;

	aux_t = tokens;
	i = 0;
	aux_t = go_to_pipe_or_first(aux_t);
	aux_t = go_to_first_word(aux_t);
	if (ft_strchr(aux_t->tok->lex, '/'))
		return (ft_strdup(aux_t->tok->lex));
	while (p->paths.mat_path[i] != NULL && aux_t->tok->type == WORD)
	{
		path = ft_strjoin(p->paths.mat_path[i++], aux_t->tok->lex);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	**defining_commands(t_dlist *tokens, size_t mat_exec_len)
{
	char	**mat_exc;
	int		i;

	i = 0;
	mat_exc = ft_calloc(sizeof(char *), mat_exec_len);
	while (tokens != NULL)
	{
		if (tokens->tok->type == WORD)
		{
			if (ft_strchr(tokens->tok->lex, '/'))
			{
				if (access(tokens->tok->lex, X_OK) == 0)
					mat_exc[i] = is_an_address(tokens->tok->lex);
				else
					mat_exc[i] = ft_strdup(tokens->tok->lex);
			}
			else
				mat_exc[i] = ft_strdup(tokens->tok->lex);
			i++;
		}
		tokens = tokens->next;
	}
	return (mat_exc);
}

char	**cria_mat_cmds(t_dlist *tokens)
{
	t_dlist	*aux;
	char	**mat_exc;
	size_t	mat_exec_len;

	mat_exec_len = 1;
	aux = tokens;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->tok->type != PIPE)
	{
		if (aux->tok->type == WORD)
			mat_exec_len++;
		if (aux->prev == NULL)
			break ;
		aux = aux->prev;
	}
	mat_exc = defining_commands(aux, mat_exec_len);
	return (mat_exc);
}

t_ast	*cria_no_cmd(t_dlist *tokens, t_pipex *p, int i, int t)
{
	t_ast	*no_cmd;

	no_cmd = (t_ast *)malloc(sizeof(t_ast));
	no_cmd->type = WORD;
	no_cmd->esq = NULL;
	no_cmd->dir = NULL;
	no_cmd->path = cria_path(tokens, p);
	no_cmd->cmd = cria_mat_cmds(tokens);
	no_cmd->files = have_redirect(tokens);
	no_cmd->r_fds.r_fd_in = 0;
	no_cmd->r_fds.r_fd_out = 0;
	if (i == t)
		no_cmd->index = 3;
	else if (i == 0)
		no_cmd->index = 1;
	else
		no_cmd->index = 2;
	return (no_cmd);
}
