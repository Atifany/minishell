#include "../minishell.h"

static void	child_redirector(int *pip, t_line *line)
{
	int		i;
	int		fd;
	char	str[100]; // make this buffer better, cuase currently programm breaks if input is greater than 100

	close(pip[WRITE]);
	ft_bzero(str, 100);
	read(pip[READ], &str, 100);
	i = 0;
	while (line->fd_to_write[i])
	{
		fd = open(line->fd_to_write[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// throw this error back with another pipe in order to actually catch it in parent
		if (fd == -1)
			printf("Error: connot open/create file %s\n", line->fd_to_write[i]);
		write(fd, str, ft_strlen(str));
		close(fd);
		i++;
	}
	write(line->pip[WRITE], str, ft_strlen(str));
	close(line->pip[WRITE]);
	close(pip[READ]);
	exit(0);
}

static char	parent_redirector(int save_out_stream, int *pip, t_line *line)
{
	char	switch_ret;

	close(pip[READ]);
	dup2(pip[WRITE], STDOUT_FILENO);
	switch_ret = ft_switch(line);
	write(1, "\0", 1); // Makes sure that if switch prints nothing child actually reads EOF,
					   // instead of endlessly waiting for input
	wait(NULL);
	close(pip[WRITE]);
	dup2(save_out_stream, STDOUT_FILENO);
	if (switch_ret)
		return (2);
	return (0);
}

// pipes won't work. top priority fix!
char	redirects(t_line *line)
{
	int		pip[2];
	pid_t	child_id;
	int		save_out_stream;
	int		save_in_stream;

	// create pipe and redirect stdout to it if there is any redirections
	save_out_stream = dup(STDOUT_FILENO);
	save_in_stream = dup(STDIN_FILENO);
	close(line->pip[WRITE]);
	dup2(line->pip[READ], STDIN_FILENO);
	if (pipe(pip) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	switch (child_id = fork())
	{
		case -1:
			printf("Fork error\n");
			return (1);
		// child
		case 0:
			child_redirector(pip, line);
		// parent
		default:
			return (parent_redirector(save_out_stream, pip, line)); // make returns clearer
	}
	close(line->pip[READ]);
	dup2(save_in_stream, STDIN_FILENO);
}
