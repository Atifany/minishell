#include"../_headers/minishell.h"

void	open_pip(int **pip)
{
	if (*pip)
		pipe(*pip);
}

void	redirect(int from, int to)
{
	dup2(to, from);
}

char	**take_input(void)
{
	char	*input_str;
	char	**exec_line;

	input_str = rl_take_input();
	if (!input_str)
		return (NULL);
	exec_line = parse_to_array(input_str);
	free(input_str);
	return (exec_line);
}

void	read_error_text(t_line *line)
{
	char	*buf;

	// get error from the switch
	redirect(STDERR_FILENO, line->save_stderr);
	close(line->pip_talk[WRITE]);
	buf = get_next_line(line->pip_talk[READ]);
	while (buf)
	{
		line->error_text = gnl_join(&(line->error_text),
			buf, ft_strlen(buf));
		free(buf);
		buf = get_next_line(line->pip_talk[READ]);
	}
	close(line->pip_talk[READ]);
}

int	exe(t_line *line)
{
	int	ret;

	ret = ft_switch(line);
	return (ret);
}

int	read_pip_status(t_line *line, int status)
{
	char	*status_from_pipe;

	close(line->pip_status[WRITE]);
	status_from_pipe = get_next_line(line->pip_status[READ]);
	close(line->pip_status[READ]);
	if (status_from_pipe)
	{
		status = ft_atoi(status_from_pipe);
		free(status_from_pipe);
	}
	return (status);
}
