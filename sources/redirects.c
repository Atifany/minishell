#include "../minishell.h"

static char	write_to_file(char *filename, char mode, char *str, size_t str_len){
	int	fd;

	fd = -1;
	if (mode == WRITE){
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
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
	int		i;
	char	str[1000];	// make this buffer better, cuase currently programm breaks
						// if input is greater than 1000

	close(line->pip_out[WRITE]);
	ft_bzero(str, 1000);
	read(line->pip_out[READ], &str, 1000);
	str_len = ft_strlen(str);
	i = 0;
	while (line->fd_to_write[i])
		write_to_file(line->fd_to_write[i++], WRITE, str, str_len);
	i = 0;
	while (line->fd_to_appwrite[i])
		write_to_file(line->fd_to_appwrite[i++], APPEND, str, str_len);
	if (line->is_piping){
		write(line->pip_in[WRITE], str, str_len);
		write(line->pip_in[WRITE], "\0", 1);
	}
	close(line->pip_out[READ]);
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
void	redirects(t_line *line, char *mode)
{
	if (!ft_strcmp(mode, "open")){
		redirect_output(line, "open");
	}
	//printf("opened\n");
	if (!ft_strcmp(mode, "close")){
		write_output(line);
		redirect_output(line, "close");
	}
}
