#include "../_headers/minishell.h"

void	write_output(t_line *line, char is_piping)
{
	size_t	str_len;
	char	*str;
	int		i;
	int		*fds;

	open_files(line, &fds);
	str = get_next_line(line->pip_out[READ]);
	while (str)
	{
		str_len = ft_strlen(str);
		i = 0;
		while (fds[i])
		{
			if (fds[i] != -1)
				write(fds[i], str, str_len);
			i++;
		}
		if (is_piping)
			write(line->pip_in[WRITE], str, str_len);
		free(str);
		str = get_next_line(line->pip_out[READ]);
	}
	close(line->pip_out[READ]);
	close_files(fds);
	free(fds);
}

void	redirect_input(t_line *line, char mode)
{
	static int	save_in_stream;

	if (mode == INIT)
	{
		save_in_stream = dup(STDIN_FILENO);
		line->pip_in = (int *)malloc(sizeof(int) * 2);
		pipe(line->pip_in);
	}
	else if (mode == OPEN)
		dup2(line->pip_in[READ], STDIN_FILENO);
	else if (mode == CLOSE)
	{
		close(line->pip_in[READ]);
		close(line->pip_in[WRITE]);
		dup2(save_in_stream, STDIN_FILENO);
	}
	else if (mode == DEINIT)
	{
		free(line->pip_in);
		line->pip_in = NULL;
	}
}
