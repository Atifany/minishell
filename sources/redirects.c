#include "../minishell.h"

static char	write_to_file(char *filename, char mode, char *str, size_t str_len){
	int	fd;

	fd = -1;
	if (mode == WRITE){
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	// THIS IS AN IMPORTANT TRY-CATCH!!!!
	// Make sure it works fine
	if (fd == -1){
		printf("Error: connot open/create file %s\n", filename);
		return (1);
	}
	write(fd, str, str_len);
	close(fd);
	return (0);
}

static void	write_output(t_line *line)
{
	size_t	str_len;
	char	*str;
	int		i;

	while (ft_cat(line->pip_out[READ], &str) > 0){
		str_len = ft_strlen(str);
		i = 0;
		while (line->fd_to_write[i])
			write_to_file(line->fd_to_write[i++], WRITE, str, str_len);
		i = 0;
		while (line->fd_to_appwrite[i])
			write_to_file(line->fd_to_appwrite[i++], APPEND, str, str_len);
		if (line->is_piping)
			write(line->pip_in[WRITE], str, str_len);
		free(str);
		str = NULL;
	}
}

void	redirect_output(t_line *line, char mode){
	static int	save_out_stream;

	if (mode == OPEN){
		save_out_stream = dup(STDOUT_FILENO);
		//printf("Rerouted output to pip_out\n");
		dup2(line->pip_out[WRITE], STDOUT_FILENO);
	}
	else if (mode == CLOSE){
		dup2(save_out_stream, STDOUT_FILENO);
		//printf("Rerouted output to stdout\n");
		write(line->pip_out[WRITE], "\0", 1);
		close(line->pip_out[WRITE]);
		write_output(line);
		close(line->pip_out[READ]);
		//printf("Sent pipe contents to recievers\n");
	}
}

void	redirect_input(t_line *line, char mode){
	static int	save_in_stream;

	if (mode == INIT){
		save_in_stream = dup(STDIN_FILENO);
		line->pip_in = (int *)malloc(sizeof(int) * 2);
		pipe(line->pip_in);
	}
	else if (mode == OPEN){
		dup2(line->pip_in[READ], STDIN_FILENO);
	}
	else if (mode == CLOSE && line->pip_in){
		close(line->pip_in[READ]);
		close(line->pip_in[WRITE]);
		dup2(save_in_stream, STDIN_FILENO);
		free(line->pip_in);
		line->pip_in = NULL;
	}
}
