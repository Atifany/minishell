/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/04/30 20:24:48 by hnickole         ###   ########.fr       */
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

static void	clear_struct(t_line *line)
{
	if (line->command)
		free(line->command);
	if (line->args)
		free_array(line->args);
	if (line->fd_to_write)
		free_array(line->fd_to_write);
	if (line->fd_to_read)
		free_array(line->fd_to_read);
}

static void	init_line(t_line *line)
{
	line->command = NULL;
	line->args = NULL;
	line->fd_to_write = NULL;
	line->fd_to_read = NULL;
	line->is_appending = FALSE;
}

static char ft_switch(t_line *line)
{
	// If, for example, I enter "exi", ft_strncmp will consider it as "exit" command and execute it.
	// That is totaly incorrect!
	if (!line->command)
		return 0;
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/')
	{
		// put program name to the args list
		// extract program name from the full path argument
		execute_file(line->command, line->args);
	}
	else if (!ft_strncmp(line->command, "pwd", ft_strlen(line->command)))
	{
		if (line->args)
			printf("pwd: too many arguments\n");
		if (execute_pwd())
			printf("Error: getcwd() failed\n");
	}
	else if (!ft_strncmp(line->command, "cd", ft_strlen(line->command)))
	{
		if (line->args && line->args[1])
			printf("cd: too many arguments\n");
		if (execute_cd(line->args[0]))
			printf("Error: %s does not exist or there is not enough memory\n", line->args[0]);
	}
	else if (!ft_strncmp(line->command, "exit", ft_strlen(line->command)))
	{
		clear_struct(line);
		return (1);
	}
	else
		printf("%s is not recognised as command\n", line->command);

	// int save_out_stream = dup(STDOUT_FILENO);
	// // first redir
	// int fd1 = open("output_file_1", O_WRONLY | O_CREAT, 0666);
	// dup2(fd1, STDOUT_FILENO);
	// close(fd1);
	// // second redir
	// int fd2 = open("output_file_2", O_WRONLY | O_CREAT, 0666);
	// dup2(fd2, STDOUT_FILENO);
	// close(fd2);
	// // go back to stdout;
	// dup2(save_out_stream, STDOUT_FILENO);
	// printf("%s\n", "It is only natural..");
	return (0);
}

int main()
{
	t_line	line;
	char	flag;
	char	input_str[100000];
	char	**exec_line;

	init_line(&line);
	ft_bzero(input_str, 100000);
	while (TRUE)
	{
		take_input(input_str); 
		//printf("Confirm input: %s\n", input_str);
		exec_line = parse_to_array(input_str);
		parse_line_to_struct(&line, exec_line);
		if (!exec_line)
		{
			printf("Error: not enough memory");
			break ;
		}
		flag = ft_switch(&line);
		free_array(exec_line);
		if (flag)
			break ;
	}
	return (0);
}