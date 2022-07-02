#include "../_headers/minishell.h"

char	open_pipe_in(t_line *line, char mode)
{
	static char	is_pipe_in_opened = FALSE;

	if (!is_pipe_in_opened)
	{
		if ((mode == OPEN && line->is_piping)
			|| (mode == APPEND && *(line->redir_input)))
		{
			is_pipe_in_opened = TRUE;
			redirect_input(line, OPEN);
		}
	}
	if (mode == CLOSE)
	{
		if (is_pipe_in_opened)
		{
			redirect_input(line, CLOSE);
			is_pipe_in_opened = FALSE;
		}
	}
	return (is_pipe_in_opened);
}

static char	read_file_to_pipe(t_line *line, char *filename)
{
	int		fd;
	char	*str;
	int		status;

	fd = open(filename, O_RDWR, 0666);
	if (fd < 0)
	{
		printf("Warning: cannot open/no such file %s\n", filename);
		return (0);
	}
	if (fork())
	{
		signal(SIGINT,SIG_IGN);
		wait(&status);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		return (0);
	}
	else
	{
		str = get_next_line(fd);
		while (str)
		{
			write(line->pip_in[WRITE], str, ft_strlen(str));
			free(str);
			str = get_next_line(fd);
		}
		exit(0);
	}
	close(fd);
}

static char	read_term_to_pipe(t_line *line, char *delimiter)
{
	char	*str;
	int		status;

	printf("listening till \"%s\"\n", delimiter);
	if (fork())
	{
		signal(SIGINT,SIG_IGN);
		wait(&status);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		return (0);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		while (TRUE)
		{
			str = readline(" > ");
			if (!str
				|| !ft_strncmp(str, delimiter, ft_strlen(delimiter)))
			{
				free(str);
				printf("\n");
				break ;
			}
			write(line->pip_in[WRITE], str, ft_strlen(str));
			write(line->pip_in[WRITE], "\n", 1);
			free(str);
		}
		exit(0);
	}
}

char	cat_to_pipe_in(t_line *line)
{
	int	i;
	int	sig;

	i = 0;
	while (line->redir_input[i])
	{
		if (line->redir_input[i]->mode == FD_READ)
		{
			sig = read_file_to_pipe(line, line->redir_input[i]->arg);
			if (sig)
				return (sig);
		}
		else
		{
			sig = read_term_to_pipe(line, line->redir_input[i]->arg);
			if (sig)
				return (sig);
		}	
		i++;
	}
	return (0);
}
