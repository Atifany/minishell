/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:57 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:22:58 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static char	is_duplicated(t_line *line, t_inqu **files, int cur)
{
	int	i;

	i = 0;
	while (i < cur)
	{
		if (!ft_strcmp(files[cur]->arg, files[i]->arg))
		{
			if (line->is_newline)
			{
				line->is_newline = FALSE;
				printf("Warning: duplicated file names ignored\n");
			}
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static void	fill_fds(t_line *line, int **fds, t_inqu **files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (is_duplicated(line, files, i))
		{
			(*fds)[i++] = -1;
			continue ;
		}	
		if (files[i]->mode == FD_WRITE)
			(*fds)[i] = open(files[i]->arg,
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			(*fds)[i] = open(files[i]->arg,
					O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((*fds)[i] == -1)
			printf("Warning: connot open/create file %s\n",
				files[i]->arg);
		i++;
	}
}

void	open_files(t_line *line, int **fds)
{
	int	size;

	size = 0;
	while (line->redir_output[size])
		size++;
	*fds = (int *)ft_calloc(size + 1, sizeof(int));
	fill_fds(line, fds, line->redir_output);
}

void	close_files(int *fds)
{
	int	i;

	i = 0;
	while (fds[i])
	{
		if (fds[i] != -1)
			close(fds[i]);
		i++;
	}
}

void	write_output(t_line *line, char is_piping)
{
	size_t	str_len;
	char	*str;
	int		i;
	int		*fds;

	open_files(line, &fds);
	str = get_next_line(line->pip_out[READ]);
	while (str)
	{
		str_len = ft_strlen(str);
		i = 0;
		while (fds[i])
		{
			if (fds[i] != -1)
				write(fds[i], str, str_len);
			i++;
		}
		if (is_piping)
			write(line->pip_in[WRITE], str, str_len);
		free(str);
		str = get_next_line(line->pip_out[READ]);
	}
	close(line->pip_out[READ]);
	close_files(fds);
	free(fds);
}
