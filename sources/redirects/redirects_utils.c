/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:48:02 by atifany           #+#    #+#             */
/*   Updated: 2022/06/26 19:32:54 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static char	is_duplicated(t_inqu **files, int cur)
{
	static char	is_first_time = TRUE;
	int	i;

	i = 0;
	while (i < cur)
	{
		if (!ft_strcmp(files[cur]->arg, files[i]->arg))
		{
			if (is_first_time)
			{
				is_first_time = FALSE;
				printf("Warning: duplicated file names ignored\n");
			}
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static void	fill_fds(int **fds, t_inqu **files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (is_duplicated(files, i++))
			continue ;
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
	fill_fds(fds, line->redir_output);
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
