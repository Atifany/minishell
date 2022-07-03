#include "../_headers/minishell.h"

char	*rl_take_input(void)
{
	char	*buf;

	buf = readline("minishell >> ");
	if (!buf)
	{
		write(1, "\n", 1);
		return (NULL);
	}
	if (*buf)
		add_history(buf);
	return (buf);
}

void	set_last_ret_env(t_line *line, int status)
{
	if (WIFSIGNALED(status))
	{
		dict_set(&(line->env),
			ft_strdup("?"), ft_itoa(WTERMSIG(status) + 128));
		write(2, "\n", 1);
	}
	else
		dict_set(&(line->env),
			ft_strdup("?"), ft_itoa(WEXITSTATUS(status)));
}

int	exe(t_line *line)
{
	int	ret;

	ret = ft_switch(line);
	return (ret);
}

char	process_input(t_line *line)
{
	char	**exec_line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_hook);
	clear_struct(line);
	init_struct(line);
	exec_line = take_input();
	if (!exec_line)
		return (1);
	if (validate(exec_line))
	{
		write(2, "Error: invalid parse instruction\n", 34);
		dict_set(&(line->env), ft_strdup("?"), ft_strdup("2"));
		free_array(exec_line);
		return (0);
	}
	if (!is_in_array(exec_line, "|"))
		simple_exe(line, exec_line);
	else
		piped_exe(line, exec_line);
	if (line->error_text)
		printf("%s", line->error_text);
	return (line->is_exit_pressed);
}
