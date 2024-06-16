/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:01:47 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/15 20:37:44 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_environ(void)
{
	hook_environ(copy_environ(), 0);
	hook_pwd(catch_cwd(), 0);
	handle_signal();
}

static char	*call_readline(void)
{
	char	*input;
	char	*entrance;

	entrance = set_entrance();
	after_prompt(0);
	input = readline(entrance);
	after_prompt(1);
	free(entrance);
	return (input);
}

int	run_program(void)
{
	t_dlist	**tokens;
	char	*input;

	init_environ();
	while (TRUE)
	{
		input = call_readline();
		if (input == NULL)
			return (interrupt_program(input));
		if (quote_validation(input))
			last_exit_status(syntax_error(UNCLOSED_QUOTE, NULL));
		else if (*input != '\0')
		{
			add_history(input);
			tokens = lexer(input);
			parser(tokens);
		}
		free(input);
	}
	return (last_exit_status(-1));
}
