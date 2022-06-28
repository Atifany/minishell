#include "../_headers/minishell.h"

// add "Warning: duplicated file names ignored"
// convert line->fd_to_write and line->fd_to_appwrite
// to t_inqu struct
static void	write_output(t_line *line)
{
	size_t	str_len;
	char	*str;
	int		i;
	int		*fds;

	open_files(line, &fds);
	while (ft_cat(line->pip_out[READ], &str) > 0)
	{
		str_len = ft_strlen(str);
		i = 0;
		while (fds[i])
		{
			if (fds[i] != -1)
				write(fds[i], str, str_len);
			i++;
		}
		if (line->is_piping)
			write(line->pip_in[WRITE], str, str_len);
		free(str);
		str = NULL;
	}
	close_files(fds);
	free(fds);
}

void	redirect_output(t_line *line, char mode)
{
	static int	save_out_stream;

	if (mode == OPEN)
	{
		save_out_stream = dup(STDOUT_FILENO);
		dup2(line->pip_out[WRITE], STDOUT_FILENO);
	}
	else if (mode == CLOSE)
	{
		dup2(save_out_stream, STDOUT_FILENO);
		write(line->pip_out[WRITE], "\0", 1);
		close(line->pip_out[WRITE]);
		write_output(line);
		close(line->pip_out[READ]);
	}
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
