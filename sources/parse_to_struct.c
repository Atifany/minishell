/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:01:59 by atifany           #+#    #+#             */
/*   Updated: 2022/04/30 20:24:51 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// think how to downsize this shit!!!!
static int	find_redirecions_runner(t_line *line, char **exec_line, char action)
{
	int	files;
	int	i;
	int	j;

	files = 0;
	j = 0;
	i = 0;
	while (exec_line[i])
	{
		if (!ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
			&& exec_line[i + 1] != NULL
			&& ft_strncmp(exec_line[i + 1], ">", ft_strlen(exec_line[i + 1])))
		{
			if (action)
				files++;
			else
				line->fd_to_write[j++] = ft_strdup(exec_line[i + 1]);
		}
		i++;
	}
	return (files);
}

static void	find_redirections(t_line *line, char **exec_line)
{
	int	files;

	if (line->fd_to_write)
		free_array(line->fd_to_write);
	line->fd_to_write = NULL;
	files = find_redirecions_runner(line, exec_line, TRUE);
	if (files == 0)
		return ;
	line->fd_to_write = (char **)malloc(sizeof(char *) * (files + 1));
	find_redirecions_runner(line, exec_line, FALSE);
	line->fd_to_write[files] = NULL;
}

static void	find_command(t_line *line, char **exec_line)
{
	int	i;

	i = 0;
	if (line->command)
		free(line->command);
	line->command = NULL;
	while (exec_line[i])
	{
		if ((ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i])) && i == 0)
			|| (ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
				&& ft_strncmp(exec_line[i - 1], ">", ft_strlen(exec_line[i - 1]))))
		{
			line->command = ft_strdup(exec_line[i]);
			break ;
		}
		i++;
	}
}

static int	find_args_runner(t_line *line, char **exec_line, char action)
{
	int		i;
	int		j;
	int		args;

	i = 0;
	j = 0;
	args = -1;
	while (exec_line[i])
	{
		if (i == 0 && ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i])))
			args++;
		if (i > 0 && ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
			&& ft_strncmp(exec_line[i - 1], ">", ft_strlen(exec_line[i - 1])))
		{
			args++;
			if (args > 0 && action)
				line->args[j++] = ft_strdup(exec_line[i]);
		}
		i++;
	}
	return (args);
}

static void	find_args(t_line *line, char **exec_line)
{
	int		args;

	if (line->args)
		free_array(line->args);
	line->args = NULL;
	if (exec_line[0] == NULL || exec_line[1] == NULL)
		return ;
	args = find_args_runner(line, exec_line, FALSE);
	if (args == 0)
		return ;
	line->args = (char **)malloc(sizeof(char *) * (args + 1));
	find_args_runner(line, exec_line, TRUE);
	line->args[args] = NULL;
}

void	parse_line_to_struct(t_line *line, char **exec_line)
{
	find_command(line, exec_line);
	find_redirections(line, exec_line);
	find_args(line, exec_line);
}

char	**parse_to_array(char *input_str)
{
	char	**array;
	int i = 0;
	int j = 0;
	char *t;

	array = ft_split(input_str, ' ');
	int array_size = arrlen(array);
	while (array[i])
	{
		j = i + 1;

		if (count(array[i], '"') % 2 == 1)
		{
			while (count(array[j], '"') == 0)
			{
				t = ft_strj(array[i], array[j]);
				free(array[i]);
				free(array[j]);
				array[i] = t;
				array[j] = NULL;
				j++;
			}
			t = ft_strj(array[i], array[j]);
			free(array[i]);
			free(array[j]);
			array[i] = t;
			array[j] = NULL;
			j++;
		}
		else if (count(array[i], '\'') % 2 == 1)
		{
			while (count(array[j], '\'') == 0)
			{
				t = ft_strj(array[i], array[j]);
				free(array[i]);
				free(array[j]);
				array[i] = t;
				array[j] = NULL;
				j++;
			}
			t = ft_strj(array[i], array[j]);
			free(array[i]);
			free(array[j]);
			array[i] = t;
			array[j] = NULL;
			j++;
		}	
		i = j;
	}
	array = dropnulls(array, array_size);
	dropquotes(array);
	return (array);
}
