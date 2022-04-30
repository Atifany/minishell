/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/04/26 20:40:01 by hnickole         ###   ########.fr       */
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

static void	init_line(t_line *line)
{
	line->command = NULL;
	line->args = NULL;
	line->fd_to_write = NULL;
	line->fd_to_read = NULL;
	line->is_appending = FALSE;
}

static void	find_redirections(t_line *line, char **exec_line)
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

static void find_command(t_line *line, char **exec_line)
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

static void find_args(t_line *line, char **exec_line)
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

static void	parse_line_to_struct(t_line *line, char **exec_line)
{
	find_command(line, exec_line);
	find_redirections(line, exec_line);
	find_args(line, exec_line);
}

static char ft_switch(t_line *line)
{
	if (!line->command)
		return 0;
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/')
	{
		//extract program name from the full path argument
		execute_file(line->command, line->args);
	}
	else if (!ft_strncmp(line->command, "pwd", ft_strlen(line->command)))
	{
		// check "too many args"
		if (execute_pwd())
			printf("Error: getcwd() failed\n");
	}
	else if (!ft_strncmp(line->command, "cd", ft_strlen(line->command)))
	{
		// check "too many args"
		if (execute_cd(line->args[0]))
			printf("Error: %s does not exist or there is not enough memory\n", line->args[0]);
	}
	else if (!ft_strncmp(line->command, "exit", ft_strlen(line->command)))
		return (1);
	else
		printf("%s is not recognised as command\n", line->command);
		/*
	if ()
	{
		cur_arg++;

		int save_out_stream = dup(STDOUT_FILENO);
		int fd = open("output.file", O_WRONLY | O_CREAT, 0666);
		dup2(fd, STDOUT_FILENO);
		printf("%s\n", exec_line[cur_arg]);
		cur_arg++;
		close(fd);
		dup2(save_out_stream, STDOUT_FILENO);
		printf("%s\n", exec_line[cur_arg]);
	}
	*/
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