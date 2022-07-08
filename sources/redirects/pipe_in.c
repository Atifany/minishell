/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:23:00 by atifany           #+#    #+#             */
/*   Updated: 2022/07/08 13:50:17 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static char	wait_reader(void)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

static char	read_file_to_pipe(t_line *line, char *filename)
{
	int		fd;
	char	*str;

	fd = open(filename, O_RDWR, 0666);
	if (fd < 0)
	{
		printf("Warning: cannot open/no such file %s\n", filename);
		return (0);
	}
	if (fork())
		return (wait_reader());
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

	printf("listening till \"%s\"\n", delimiter);
	if (fork())
		return (wait_reader());
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
	while (line->redir_input[i] && line->redir_input[i + 1])
		i++;
	if (line->redir_input[i])
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
	}
	return (0);
}
