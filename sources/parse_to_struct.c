/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:01:59 by atifany           #+#    #+#             */
/*   Updated: 2022/05/02 17:33:20 by hnickole         ###   ########.fr       */
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
		while (input_str[j] == ' '&& input_str[j] != 0)
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
	int		*len_arr = ft_calloc(count(input_str, ' '), 8);

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
