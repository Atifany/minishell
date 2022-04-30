/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:01:59 by atifany           #+#    #+#             */
/*   Updated: 2022/04/30 20:02:00 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_redirections(t_line *line, char **exec_line)
{
	int	files;
	int	i;
	int	j;

	files = 0;
	i = 0;
	line->fd_to_write = NULL;
	while (exec_line[i])
	{
		if (!ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
			&& exec_line[i + 1] != NULL
			&& ft_strncmp(exec_line[i + 1], ">", ft_strlen(exec_line[i + 1])))
			files++;
		i++;
	}
	if (files == 0)
		return ;
	line->fd_to_write = (char **)malloc(sizeof(char *) * (files + 1));
	j = 0;
	i = 0;
	while (exec_line[i])
	{
		if (!ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
			&& exec_line[i + 1] != NULL
			&& ft_strncmp(exec_line[i + 1], ">", ft_strlen(exec_line[i + 1])))
			line->fd_to_write[j++] = ft_strdup(exec_line[i + 1]);
		i++;
	}
	line->fd_to_write[j] = NULL;
}

void	find_command(t_line *line, char **exec_line)
{
	int	i;

	i = 0;
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

void	find_args(t_line *line, char **exec_line)
{
	char	flag;
	int		args;
	int		i;
	int		j;

	flag = TRUE;
	args = 0;
	i = 0;
	line->args = NULL;
	while (exec_line[i])
	{
		if (i == 0 && ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i])))
			flag = FALSE;
		if (i != 0
			&& ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
			&& ft_strncmp(exec_line[i - 1], ">", ft_strlen(exec_line[i - 1])))
		{
			if (!flag)
				args++;
			flag = FALSE;
		}
		i++;
	}
	if (args == 0)
		return ;
	line->args = (char **)malloc(sizeof(char *) * (args + 1));
	flag = TRUE;
	j = 0;
	i = 0;
	while (exec_line[i])
	{
		if (i == 0 && ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i])))
			flag = FALSE;
		if (i != 0
			&& ft_strncmp(exec_line[i], ">", ft_strlen(exec_line[i]))
			&& ft_strncmp(exec_line[i - 1], ">", ft_strlen(exec_line[i - 1])))
		{
			if (!flag)
				line->args[j++] = ft_strdup(exec_line[i]);
			flag = FALSE;
		}
		i++;
	}
	line->args[j] = NULL;
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
		if (contains(array[i], '"'))
		{
			while (!contains(array[j], '"'))
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
	for (int l = 0; l < arrlen(array); l++)
		printf("||%s\n", array[l]);	
	return (array);
}
