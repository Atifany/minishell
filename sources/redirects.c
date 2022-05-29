#include "../minishell.h"

static void	child_redirector(t_line *line)
{
	size_t	str_len;
	int		i;
	int		fd;
	char	str[1000];	// make this buffer better, cuase currently programm breaks
						// if input is greater than 1000

	close(line->pip_out[WRITE]);
	ft_bzero(str, 1000);
	read(line->pip_out[READ], &str, 1000);
	str_len = ft_strlen(str);
	i = 0;
	while (line->fd_to_write[i])
	{
		fd = open(line->fd_to_write[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// THIS IS AN IMPORTANT TRY-CATCH!!!!
		// throw this error back with another pipe in order to actually catch it in parent
		if (fd == -1)
			printf("Error: connot open/create file %s\n", line->fd_to_write[i]);
		write(fd, str, str_len);
		close(fd);
		i++;
	}
	if (line->is_piping){
		write(line->pip_in[WRITE], str, str_len);
		write(line->pip_in[WRITE], "\0", 1);
	}
	close(line->pip_out[READ]);
	exit(0);
}

static char	parent_redirector(t_line *line)
{
	char	switch_ret;

	switch_ret = ft_switch(line);
	write(1, "\0", 1); // Makes sure that if switch prints nothing child actually reads EOF,
					   // instead of endlessly waiting for input
	wait(NULL);
	if (switch_ret)
		return (2);
	return (0);
}

void	redirect_output(t_line *line, char *mode){
	static int	save_out_stream;

	if (!ft_strcmp(mode, "open")){
		save_out_stream = dup(STDOUT_FILENO);
		dup2(line->pip_out[WRITE], STDOUT_FILENO);
	}
	else if (!ft_strcmp(mode, "close")){
		dup2(save_out_stream, STDOUT_FILENO);
		close(line->pip_out[READ]);
		close(line->pip_out[WRITE]);
	}
}

// pipes won't work. top priority fix!
char	redirects(t_line *line)
{
	char	ret;
	pid_t	child_id;

	redirect_output(line, "open");
	switch (child_id = fork())
	{
		case -1:
			printf("Fork error\n");
			return (1);
		// child
		case 0:
			child_redirector(line);
		// parent
		default:
			ret = parent_redirector(line); // make returns clearer
			redirect_output(line, "close");
			return (ret);
	}
}
