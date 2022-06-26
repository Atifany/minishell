/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:48:02 by atifany           #+#    #+#             */
/*   Updated: 2022/06/26 15:48:35 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static void	fill_fds(int **fds, char **files, char mode)
{
	int	j;
	int	i;

	i = 0;
	while ((*fds)[i])
		i++;
	j = 0;
	while (files[j])
	{
		if (mode == OPEN)
			(*fds)[i] = open(files[j],
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			(*fds)[i] = open(files[j],
					O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((*fds)[i] == -1)
			printf("Warning: connot open/create file %s\n",
				files[j]);
		i++;
		j++;
	}
}

void	open_files(t_line *line, int **fds)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (line->fd_to_write[i])
		i++;
	size += i;
	i = 0;
	while (line->fd_to_appwrite[i])
		i++;
	size += i;
	*fds = (int *)ft_calloc(size + 1, sizeof(int));
	fill_fds(fds, line->fd_to_write, OPEN);
	fill_fds(fds, line->fd_to_appwrite, APPEND);
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
