#include "../_headers/minishell.h"

int	ft_switch(t_line *line)
{
	t_func	*f;

	if (!line->command[0])
		return (0);
	if (!ft_strcmp(line->command, "exit"))
	{
		line->is_exit_pressed = TRUE;
		return (0);
	}
	f = (t_func *)dict_get(&(line->func_dict), line->command);
	if (!f)
		return (execute_file(line));
	else
		return (f->foo(line));
	return (0);
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
	init_streams(&line);
	init_struct(&line);
	g_child_pid = 0;
	rotate = 0;
	// bind exit command to a flag in struct, so that it executes
	// in single cmd and not in piped cmd
	while (!rotate)
		rotate = process_input(&line);
	rl_clear_history();
	clear_dicts(&line);
	clear_struct(&line);
	clear_pips(&line);
	return (0);
}
