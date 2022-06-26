/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:12:32 by atifany           #+#    #+#             */
/*   Updated: 2022/06/26 15:50:18 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	read_file_to_pipe(t_line *line, char *filename)
{
	int		fd;
	char	*str;

	fd = open(filename, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
	{
		printf("Error: cannot open/create file %s\n", filename);
		return ;
	}
	while (ft_cat(fd, &str) > 0)
	{
		write(line->pip_in[WRITE], str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	close(fd);
}

void	read_term_to_pipe(t_line *line, char *delimiter)
{
	char	*str;

	while (TRUE)
	{
		str = get_next_line(1);
		if (!str
			|| (!ft_strncmp(str, delimiter,
					ft_strlen(delimiter) - 1)
				&& ft_strlen(str) - ft_strlen(delimiter) == 1))
		{
			free(str);
			break ;
		}
		write(line->pip_in[WRITE], str, ft_strlen(str));
		free(str);
	}
}

void	cat_to_pipe_in(t_line *line)
{
	int	i;

	i = 0;
	while (line->redir_input[i])
	{
		if (line->redir_input[i]->mode == 0)
			read_file_to_pipe(line, line->redir_input[i]->arg);
		else
			read_term_to_pipe(line, line->redir_input[i]->arg);
		i++;
	}
}
