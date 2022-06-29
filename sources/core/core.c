#include "../_headers/minishell.h"

char	ft_switch(t_line *line)
{
	t_func	*f;

	if (!ft_strcmp(line->command, "exit"))
		return (1);
	if (!line->command[0])
		return (0);
	f = (t_func *)dict_get(&(line->func_dict), line->command);
	if (!f)
	{
		execute_file(line);
		return (0);
	}
	else
		f->foo(line);
	return (0);
}

// ^C must end reading from stdin and stop all execution
void	sighandler(int sig)
{
	(void)sig;
	if (g_child_pid != 0)
	{
		kill(g_child_pid, SIGINT);
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\0", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

static void	clear_dicts(t_line *line)
{
	dict_del(&(line->env));
	dict_del(&(line->func_dict));
}

int	main(void)
{
	char	rotate;
	t_line	line;

	init_env(&line);
	func_dict_init(&line);
	init_struct(&line);
	g_child_pid = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
	rotate = 0;
	while (!rotate)
		rotate = process_input(&line);
	rl_clear_history();
	clear_dicts(&line);
	clear_struct(&line);
	return (0);
}
