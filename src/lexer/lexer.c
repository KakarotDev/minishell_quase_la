/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:42:03 by myokogaw          #+#    #+#             */
/*   Updated: 2024/03/26 19:42:03 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handling_single_quotes(char *input, int fd)
{
	if (input == NULL)
		return (input);
	input += write(fd, input, 1);
	while (*input != '\'')
		input += write(fd, input, 1);
	input += write(fd, input, 1);
	return (input);
}

static char	*handling_double_quotes(char *input, int fd)
{
	if (input == NULL)
		return (input);
	input += write(fd, input, 1);
	while (*input != '\"')
		input += write(fd, input, 1);
	input += write(fd, input, 1);
	return (input);
}

static char	*handling_ops(char *input, int fd)
{
	if (!ft_strncmp(input, "<<", 2)
		|| !ft_strncmp(input, ">>", 2))
	{
		write(fd, "\n", 1);
		input += write(fd, input, 2);
		write(fd, "\n", 1);
	}
	else if (!ft_strncmp(input, "<", 1)
		|| !ft_strncmp(input, ">", 1)
		|| !ft_strncmp(input, "|", 1))
	{
		write(fd, "\n", 1);
		input += write(fd, input, 1);
		write(fd, "\n", 1);
	}
	return (input);
}

t_dlist	**lexer(char *input)
{
	t_dlist	**tokens;
	int		fd;

	fd = ft_open_fd("/tmp/.input_minishell", OPEN_WR);
	while (*input != '\0' && (*input == ' ' || *input == '\t'))
		input++;
	while (*input)
	{
		if (*input == ' ')
			input = ft_isspace(input, fd);
		if (*input == '\'')
			input = handling_single_quotes(input, fd);
		if (*input == '\"')
			input = handling_double_quotes(input, fd);
		if (ft_have_op(input))
			input = handling_ops(input, fd);
		if (*input != '\'' && *input != '\"'
			&& *input != ' ' && *input != 0)
			input += write(fd, input, 1);
	}
	close(fd);
	received_sigint_in_heredoc(0);
	tokens = generate_tokens("/tmp/.input_minishell");
	return (tokens);
}
