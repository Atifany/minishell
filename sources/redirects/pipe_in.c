#include "../_headers/minishell.h"

char	open_pipe_in(t_line *line, char mode){
	static char	is_pipe_in_opened = FALSE;

	if (!is_pipe_in_opened){
		if ((line->is_piping && mode == OPEN) ||
			(*(line->redir_input) && mode == APPEND)){
			is_pipe_in_opened = TRUE;
			redirect_input(line, OPEN);
		}
	}
	if (mode == CLOSE){
		if (is_pipe_in_opened){
			redirect_input(line, CLOSE);
			is_pipe_in_opened = FALSE;
		}
	}
	return (is_pipe_in_opened);
}

void	read_file_to_pipe(t_line *line, char *filename){
	int		fd;
	char	*str;

	fd = open(filename, O_CREAT | O_RDWR, 0666);
	while (ft_cat(fd, &str) > 0){
		write(line->pip_in[WRITE], str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	close(fd);
}

void read_term_to_pipe(t_line *line, char *delimiter){
	char *str;

	while (TRUE){
		str = get_next_line(1);
		//printf(">>> %s|%s|%d|%d\n", str, delimiter,
		//	ft_strncmp(str, delimiter, ft_strlen(delimiter) - 1), str[ft_strlen(delimiter)]);
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter) - 1)
			&& ft_strlen(str) - ft_strlen(delimiter) == 1){
			free(str);
			break;
		}
		write(line->pip_in[WRITE], str, ft_strlen(str));
		free(str);
	}
}

void	cat_to_pipe_in(t_line *line){
	
	int		i = 0;
	

	while (line->redir_input[i]){
		if (line->redir_input[i]->mode == 0){
			read_file_to_pipe(line, line->redir_input[i]->arg);
		}
		else{
			read_term_to_pipe(line, line->redir_input[i]->arg);
		}
		i++;
	}
}
