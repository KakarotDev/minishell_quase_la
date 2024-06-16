/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:36:08 by myokogaw          #+#    #+#             */
/*   Updated: 2024/06/16 04:04:36 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	receive_sig_int_heredoc(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	close(STDIN_FILENO);
	received_sigint_in_heredoc(1);
	last_exit_status(128 + sig);
}

void	handle_signal_heredoc(void)
{
	struct sigaction	sigint_here;

	sigemptyset(&sigint_here.sa_mask);
	sigint_here.sa_handler = receive_sig_int_heredoc;
	sigint_here.sa_flags = 0;
	sigaction(SIGINT, &sigint_here, NULL);
}

int	after_prompt(int is_after)
{
	static int	prompt;

	if (is_after != -1)
		prompt = is_after;
	return (prompt);
}

void	receive_sig_int(int sig)
{
	if (!is_process(-1))
		ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (!after_prompt(-1))
		rl_redisplay();
	last_exit_status(128 + sig);
}

void	handle_signal(void)
{
	struct sigaction	sigint_std;
	struct sigaction	sigquit_std;

	sigemptyset(&sigint_std.sa_mask);
	sigint_std.sa_handler = receive_sig_int;
	sigint_std.sa_flags = 0;
	sigemptyset(&sigquit_std.sa_mask);
	sigquit_std.sa_handler = SIG_IGN;
	sigquit_std.sa_flags = 0;
	sigaction(SIGINT, &sigint_std, NULL);
	sigaction(SIGQUIT, &sigquit_std, NULL);
}
