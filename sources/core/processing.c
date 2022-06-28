#include "../_headers/minishell.h"

static char	*take_input(void)
{
	char	*buf;

	buf = readline("minishell >> ");
	if (!buf)
	{
		printf("\n");
		return (NULL);
	}
	if (*buf)
		add_history(buf);
	return (buf);
}

static int	pre_handle(t_line *line, char **exec_line)
{
	char	is_pipe_in_opened;
	int		shift;

	is_pipe_in_opened = open_pipe_in(line, OPEN);
	shift = parse_line_to_struct(line, exec_line);
	variable_handler((line->args), &(line->env));
	is_pipe_in_opened = open_pipe_in(line, APPEND);
	if (*(line->redir_input))
		cat_to_pipe_in(line);
	if (is_pipe_in_opened)
		write(line->pip_in[WRITE], "\0", 1);
	return (shift);
}

static char	iterate_exec_line(char **exec_line, t_line *line)
{
	char	ret;
	int		total_shift;
	int		shift;

	shift = 0;
	total_shift = 0;
	while (*exec_line)
	{
		shift = pre_handle(line, exec_line);
		total_shift += shift;
		exec_line += shift;
		if (line->is_redirecting)
			redirect_output(line, OPEN);
		ret = ft_switch(line);
		if (line->is_redirecting)
			redirect_output(line, CLOSE);
		if (ret)
		{
			open_pipe_in(line, CLOSE);
			return (1);
		}
		if (((char *)(dict_get(&(line->env), "?")))[0] != '0')
			print_error(line);			
	}
	exec_line -= total_shift;
	open_pipe_in(line, CLOSE);
	return (0);
}

char	process_input(t_line *line)
{
	char	**exec_line;
	char	*input_str;
	char	rotate;

	input_str = NULL;
	clear_struct(line);
	init_struct(line);
	input_str = take_input();
	if (!input_str)
		return (1);
	redirect_input(line, INIT);
	exec_line = parse_to_array(input_str);
	free(input_str);
	input_str = NULL;
	line->is_newline = TRUE;
	rotate = iterate_exec_line(exec_line, line);
	free_array(exec_line);
	redirect_input(line, DEINIT);
	return (rotate);
}
