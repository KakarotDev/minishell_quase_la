#include "minishell.h"

// void	sig_handler(void)
// {
// 	signal(SIGQUIT, SIG_DFL);
// }
// void	sig_handler(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_DFL);
// }

// int	main(void)
// {
// 	sig_handler();
	// raise(SIGQUIT);
	// while (1)
	// 	;
	// raise(SIGINT);
// }


// void	receive_sig_int(int sig)
// {
// 	// if (its_in_heredoc(-1))
// 	// 	close(STDIN_FILENO);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	// last_exit_status(128 + sig);
// }

// void	handle_signal(void)
// {
// 	struct sigaction sigint_std;
// 	struct sigaction sigquit_std;
	
// 	sigemptyset(&sigint_std.sa_mask);
// 	sigint_std.sa_handler = receive_sig_int;
// 	sigint_std.sa_flags = 0;
// 	sigemptyset(&sigquit_std.sa_mask);
// 	sigquit_std.sa_handler = SIG_IGN;
// 	sigquit_std.sa_flags = 0;
// 	sigaction(SIGINT, &sigint_std, NULL);
// 	sigaction(SIGQUIT, &sigquit_std, NULL);
// }

int	main(void)
{
	struct stat test;

	if (lstat("./src", &test))
		printf("Is a directory");
	return (0);
}
