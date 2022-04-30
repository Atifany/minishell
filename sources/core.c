/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/04/30 15:48:28 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	take_input(char *input_str)
{
	char	*buf;

	buf = readline("\e[0;36mminishell \e[1;36m>> \e[0m");
	ft_strlcpy(input_str, buf, 100000);
	free(buf);
	return (0);
}

static char **parse_to_array(char *input_str)
{
	char	**array;
	array = ft_split(input_str, ' ');
	return (array);
}

static char ft_switch(char **exec_line)
{
	if (exec_line == NULL || *exec_line == NULL)
		return 0;
	else if (!ft_strncmp(exec_line[0], "./", 2))
	{
		//check if correct line was passed
		execute_file(*exec_line, exec_line);
		//catch error if present
	}
	else if (!ft_strncmp(exec_line[0], "pwd", ft_strlen(exec_line[0])))
	{
		if (print_dir())
			printf("Error: getcwd() failed\n");
	}
	else if (!ft_strncmp(exec_line[0], "cd", ft_strlen(exec_line[0])))
	{
		if (execute_cd(exec_line[1]))
			printf("Error: %s does not exist or there is not enough memory\n", exec_line[1]);
	}
	else if (!ft_strncmp(exec_line[0], "exit", ft_strlen(exec_line[0])))
		return (1);
	else
		printf("%s is not recognised as command\n", exec_line[0]);
	return (0);
}

int main()
{
	char	flag;
	char	input_str[100000];
	char	**exec_line;

	ft_bzero(input_str, 100000);
	while (TRUE)
	{
		take_input(input_str); 
		//printf("Confirm input: %s\n", input_str);
		exec_line = parse_to_array(input_str);
		if (!exec_line)
		{
			printf("Error: not enough memory");
			break ;
		}
		flag = ft_switch(exec_line);
		free_array(exec_line);
		if (flag)
			break ;
	}
	return (0);
}