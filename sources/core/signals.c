#include "../_headers/minishell.h"

// core sigint_hook. clears readline.
void	sigint_hook(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	signals_default()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_ignore()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
