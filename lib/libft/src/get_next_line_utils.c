/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:46:29 by myokogaw          #+#    #+#             */
/*   Updated: 2024/01/09 15:56:42 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_byte	*ft_newnode(char content)
{
	t_byte	*new;

	new = (t_byte *) malloc(1 * sizeof(t_byte));
	new->next = NULL;
	new->byte = content;
	return (new);
}

void	ft_addend_list(t_byte **start, t_byte *new_c)
{
	t_byte	*temp;

	if (!new_c)
		return ;
	if (!*start)
	{
		*start = new_c;
		return ;
	}
	temp = *start;
	while (temp->next)
		temp = temp->next;
	temp->next = new_c;
}

char	*ft_cpybuffer(t_vars *vars)
{
	while (1)
	{
		ft_addend_list(&vars->str, ft_newnode(*(vars->buffer + vars->iter)));
		if (*(vars->buffer + vars->iter) == '\0' || \
		*(vars->buffer + vars->iter) == '\n')
			break ;
		vars->iter++;
		vars->len++;
		if (vars->iter >= vars->bytes_read)
		{
			vars->iter = 0;
			vars->bytes_read = read(vars->fd, vars->buffer, BUFFER_SIZE);
			if (vars->bytes_read <= 0)
				break ;
		}
	}
	vars->iter++;
	vars->len++;
	return (ft_returnline(vars));
}

char	*ft_returnline(t_vars *vars)
{
	t_byte		*temp;
	char		*line;
	long long	i;

	line = (char *) malloc((vars->len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (vars->str)
	{
		temp = vars->str->next;
		line[i] = vars->str->byte;
		free(vars->str);
		vars->str = temp;
		i++;
	}
	*(line + i) = '\0';
	return (line);
}
