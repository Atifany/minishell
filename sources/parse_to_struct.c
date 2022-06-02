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

char	is_arrow(char *str){
	if (!ft_strcmp(str, ">") ||
		!ft_strcmp(str, ">>") ||
		!ft_strcmp(str, "<") ||
		!ft_strcmp(str, "<<"))
	{
		return (TRUE);
	}
	return (FALSE);
}

static char	identify(char **exec_line, int i){
	if (i == 0){
		if (!is_arrow(exec_line[i])){
			return (ARG);
		}
		return (ARROW);
	}
	if (!is_arrow(exec_line[i]) && !is_arrow(exec_line[i - 1])){
		return (ARG);
	}
	if (!is_arrow(exec_line[i]) && is_arrow(exec_line[i - 1])){
		if (!ft_strcmp(exec_line[i - 1], ">")){
			return (FD_WRITE);
		}
		if (!ft_strcmp(exec_line[i - 1], ">>")){
			return (FD_AP_WRITE);
		}
		if (!ft_strcmp(exec_line[i - 1], "<")){
			return (FD_READ);
		}
		if (!ft_strcmp(exec_line[i - 1], "<<")){
			return (FD_AP_READ);
		}
	}
	return (ERROR);
}

static int	iterate_line(char **exec_line, char **arr, char to_search, char mode){
	int	ret = 0;
	int i = 0;
	int j = 0;

	while (exec_line[i]){
		if (!ft_strcmp(exec_line[i], "|")){
			break ;
		}
		if (identify(exec_line, i) == to_search){
			if (mode == COUNT){
				ret++;
			}
			if (mode == COLLECT){
				arr[j++] = ft_strdup(exec_line[i]);
			}
		}
		i++;
	}
	return (ret);
}

// tmp func. Delete it later.
void	temp_print_struct(t_line *line){
	int i;

	printf("command: %s\n", line->command);
	printf("args: ");
	i = 0;
	while (line->args[i]){
		printf("%s ", line->args[i++]);
	}
	printf("\n");
	printf("writes: ");
	i = 0;
	while (line->fd_to_write[i]){
		printf("%s ", line->fd_to_write[i++]);
	}
	printf("\n");
	printf("app writes: ");
	i = 0;
	while (line->fd_to_appwrite[i]){
		printf("%s ", line->fd_to_appwrite[i++]);
	}
	printf("\n");
}

void	refresh_pip_out(t_line *line){
	if (line->pip_out){
		free(line->pip_out);
		line->pip_out = NULL;
	}
	line->pip_out = malloc(sizeof(int) * 2);
	pipe(line->pip_out);
}

static int	parse(char **exec_line, char ***arr, char to_search){
	int	ret;

	if (*arr){
		free_array(*arr);
	}
	*arr = NULL;
	ret = iterate_line(exec_line, *arr, to_search, COUNT);
	*arr = (char **)malloc(sizeof(char *) * (ret + 1));
	iterate_line(exec_line, *arr, to_search, COLLECT);
	(*arr)[ret] = NULL;
	return (ret);
}

int	parse_line_to_struct(t_line *line, char **exec_line)
{
	int	total_shift;

	refresh_pip_out(line);
	total_shift = parse(exec_line, &(line->args), ARG);
	line->command = ft_strdup(line->args[0]);
	// multyplied by two because "> keks.txt"
	total_shift += 2 * parse(exec_line, &(line->fd_to_write), FD_WRITE);
	total_shift += 2 * parse(exec_line, &(line->fd_to_appwrite), FD_AP_WRITE);
	total_shift += 2 * parse(exec_line, &(line->fd_to_read), FD_READ);
	total_shift += 2 * parse(exec_line, &(line->fd_to_appread), FD_AP_READ);

	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	if (*(exec_line + total_shift) != NULL){ // That means find_* funcs stoped at pipe, not a EOL
		line->is_piping = TRUE;
		line->is_redirecting = TRUE;
		total_shift++;
	}
	if (*(line->fd_to_write) || *(line->fd_to_appwrite)){
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
