/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:01:59 by atifany           #+#    #+#             */
/*   Updated: 2022/05/02 18:32:49 by hnickole         ###   ########.fr       */
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
		if (!ft_strcmp(exec_line[i], "|")){
			break ;
			//return (files + 1);
		}
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

static int	find_redirections(t_line *line, char **exec_line)
{
	int	files;

	if (line->fd_to_write){
		free_array(line->fd_to_write);
	}
		
	line->fd_to_write = NULL;
	files = find_redirecions_runner(line, exec_line, TRUE);
	line->fd_to_write = (char **)malloc(sizeof(char *) * (files + 1));
	if (files > 0)
		find_redirecions_runner(line, exec_line, FALSE);
	line->fd_to_write[files] = NULL;
	return (files);
}

static void	find_command(t_line *line, char **exec_line)
{
	int	i;

	i = 0;
	if (line->command){
		free(line->command);
	}
		
	line->command = NULL;
	while (exec_line[i])
	{
		if (!ft_strcmp(exec_line[i], "|")){
			break ;
		}
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
		if (!ft_strcmp(exec_line[i], "|")){
			break ;
		}
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

static int	find_args(t_line *line, char **exec_line)
{
	int		args;

	if (line->args){
		free_array(line->args);
	}
		
	line->args = NULL;
	//if (exec_line[0] == NULL || exec_line[1] == NULL)
	//	return ();
	args = find_args_runner(line, exec_line, FALSE);
	if (args < 1)
		args = 0;
	line->args = (char **)malloc(sizeof(char *) * (args + 1));
	if (args > 0)
		find_args_runner(line, exec_line, TRUE);
	line->args[args] = NULL;
	return (args);
}

void	temp_print_struct(t_line *line){
	int i;

	printf("command: %s\n", line->command);
	printf("args: ");
	i = 0;
	while (line->args[i]){
		printf("%s ", line->args[i++]);
	}
	printf("\n");
	printf("redirects: ");
	i = 0;
	while (line->fd_to_write[i]){
		printf("%s ", line->fd_to_write[i++]);
	}
	printf("\n");
}

int	parse_line_to_struct(t_line *line, char **exec_line)
{
	if (line->pip_out){
		free(line->pip_out);
		line->pip_out = NULL;
	}
	line->pip_out = malloc(sizeof(int) * 2);
	pipe(line->pip_out);

	int	total_shift = 1; // one and not a zero is because the command must be present!
	find_command(line, exec_line);
	total_shift += find_redirections(line, exec_line) * 2;
	total_shift += find_args(line, exec_line);
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	if (*(exec_line + total_shift) != NULL){ // That means find_* funcs stoped at pipe, not a EOL
		line->is_piping = TRUE;
		line->is_redirecting = TRUE;
		total_shift++;
	}
	if (*(line->fd_to_write)){
		line->is_redirecting = TRUE;
	}
	//temp_print_struct(line);
	return (total_shift);
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
