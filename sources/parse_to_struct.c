/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:01:59 by atifany           #+#    #+#             */
/*   Updated: 2022/05/02 18:06:44 by hnickole         ###   ########.fr       */
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

void len_arr_inc(void *len_arr, int i, char str)
{
	str = 0;
	((int *)(len_arr))[i]++;
}

void copy_symbol(void *arr, int i, char str)
{
	*(((char **)(arr))[i]) = str;
	((char **)arr)[i]++;
}

int helper(char *input_str, void f(void *, int, char), void *arr)
{
	int		i = 0;
	int		j = 0;

	while (input_str[j] != 0)
	{
		while (input_str[j] == ' ')
			j++;
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"')
			{
				j++;
				while (input_str[j] != '"')//catch error of unclosed quotes here
					f(arr, i, input_str[j++]);
				j++;
			}
			else if (input_str[j] == '\'')
			{
				j++;
				while (input_str[j] != '\'')//catch error of unclosed quotes here
					f(arr, i, input_str[j++]);
				j++;
			}
			else
				f(arr, i, input_str[j++]);
		}
		i++; 
		if (input_str[j] != 0)
			j++;
	}
	return i;
}

char	**parse_to_array(char *input_str)
{
	char	**arr;
	int		*len_arr = ft_calloc(count(input_str, ' ') + 1, 8);

	int i = helper(input_str, *len_arr_inc, len_arr);	
	arr = malloc(8 * (i + 1));	
	arr[i] = NULL;
	while (--i >= 0)
		arr[i] = ft_calloc(len_arr[i] + 1, 1);	
	i = helper(input_str, *copy_symbol, arr);	
	while (--i >= 0)
		arr[i] = arr[i]-len_arr[i];
	free(len_arr);
	return (arr);
}
