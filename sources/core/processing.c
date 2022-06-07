#include "../_headers/minishell.h"

static char	*take_input()
{
	char	*buf;

	buf = readline("\e[0;36mminishell \e[1;36m>> \e[0m");
	return (buf);
}

static int	pre_handle(t_line *line, char **exec_line)
{
	char	is_pipe_in_opened;
	int		shift;

	is_pipe_in_opened = open_pipe_in(line, OPEN);	// called on
													// the SECOND time
													// right after pipe
	shift = parse_line_to_struct(line, exec_line);
	is_pipe_in_opened = open_pipe_in(line, APPEND);	// called on < or <<
	if (*(line->redir_input)){
		cat_to_pipe_in(line);
	}
	if (is_pipe_in_opened){
		write(line->pip_in[WRITE], "\0", 1);
	}
	return (shift);
}

static char	iterate_exec_line(char **exec_line, t_line *line)
{
	char	ret;
	int		total_shift;	// represents total shift on exec_line
	int		shift;			// represents current cmd shift on exec_line

	shift = 0;
	total_shift = 0;
	while (*exec_line){		// iterates each command in current line
		shift = pre_handle(line, exec_line);
		total_shift += shift;
		exec_line += shift;
		if (line->is_redirecting){
			redirect_output(line, OPEN);
		}
		ret = ft_switch(line);
		if (line->is_redirecting){
			redirect_output(line, CLOSE);
		}
		if (ret) // switch returned exit code.
			return (1);
	}
	exec_line -= total_shift;
	open_pipe_in(line, CLOSE);
	return (0);
}

char	process_input(t_line *line)
{
	char	**exec_line;
	char	*input_str = NULL;
	char	rotate;

	clear_struct(line);
	init_struct(line); // I guess it leaks, so add free() inside this func
	redirect_input(line, INIT);
	input_str = take_input();
	exec_line = parse_to_array(input_str);
	free(input_str);
	input_str = NULL;
	if (!exec_line){
		printf("Error: not enough memory\n");
		return (1);
	}
	rotate = iterate_exec_line(exec_line, line);
	free_array(exec_line);
	return (rotate);
}
