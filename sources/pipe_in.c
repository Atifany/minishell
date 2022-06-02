# include "../minishell.h"

char	open_pipe_in(t_line *line, char mode){
	static char	is_pipe_in_opened = FALSE;

	if (mode == OPEN){
		if (line->is_piping && !is_pipe_in_opened){
			is_pipe_in_opened = TRUE;
			redirect_input(line, OPEN);
		}
	}
	else if (mode == APPEND){
		if (*(line->fd_to_read) && !is_pipe_in_opened){
			is_pipe_in_opened = TRUE;
			redirect_input(line, OPEN);
		}
	}
	else{
		if (is_pipe_in_opened){
			redirect_input(line, CLOSE);
			is_pipe_in_opened = FALSE;
		}
	}
	return (is_pipe_in_opened);
}

void	cat_to_pipe_in(t_line *line){
	char	*str;
	int		i = 0;
	int		fd;

	while (line->fd_to_read[i]){
		fd = open(line->fd_to_read[i], O_CREAT | O_RDWR, 0666);
		while (ft_cat(fd, &str) > 0){
			write(line->pip_in[WRITE], str, ft_strlen(str));
			free(str);
			str = NULL;
		}
		close(fd);
		i++;
	}
}
