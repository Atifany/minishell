/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/05/02 21:02:13 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	take_input(char *input_str)
{
	char	*buf;

	buf = readline("\e[0;36mminishell \e[1;36m>> \e[0m");
	//printf("Input: %s\n", buf);
	ft_strlcpy(input_str, buf, 100000);
	if (buf)
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
	// If, for example, I enter "exi", ft_strncmp will consider it as "exit" command and execute it,
	// which is totaly incorrect!
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
	return (0);
}

static char	redirects(t_line *line)
{
	char	str[100]; // make this buffer better, cuase currently programm breaks if input is greater than 100
	int		i;
	int		fd;
	int		pip[2];
	pid_t	child_id = 1;
	int		save_out_stream;

	if (!line->fd_to_write)
	{
		ft_switch(line);
		return (0);
	}
	// create pipe and redirect stdout to it if there is any redirections
	save_out_stream = dup(STDOUT_FILENO);
	if (pipe(pip) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	switch (child_id = fork())
	{
		case -1:
			printf("Fork error\n");
			return (1);
		// child
		case 0:
			close(pip[WRITE]);
			ft_bzero(str, 100);
			read(pip[READ], &str, 100);
			i = 0;
			while (line->fd_to_write[i])
			{
				fd = open(line->fd_to_write[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
				// throw this error back with another pipe in order to actually catch it in parent
				if (fd == -1)
					printf("Error: connot open/create file %s\n", line->fd_to_write[i]);
				write(fd, str, ft_strlen(str));
				close(fd);
				i++;
			}
			close(pip[READ]);
			exit(0);
		// parent
		default:
			close(pip[READ]);
			dup2(pip[WRITE], STDOUT_FILENO);
			if (ft_switch(line))
			{
				wait(NULL);
				close(pip[WRITE]);
				dup2(save_out_stream, STDOUT_FILENO);
				return (2);
			}
			wait(NULL);
			close(pip[WRITE]);
			dup2(save_out_stream, STDOUT_FILENO);
	}
	return (0);
}

void	sighandler(int sig)
{
		//printf("%x\n", RL_READLINE_VERSION);
		//rl_redisplay();
		//rl_replace_line();
		//rl_on_new_line();
		if (child_pid != 0)
		{
			printf("kill child");
			kill(child_pid, SIGINT);
			write(1, "\n", 1);
		}
		// else
		// {
		// 	rl_replace_line("", 0);
		// 	//rl_line_buffer = malloc(ft_strlen("AMONGUS! HIHIHIHIHIHIHIHIHI"));
		// 	//rl_line_buffer = "AMONGUS! HIHIHIHIHIHIHIHIHI";
		// }
		sig = 0;
}

int main()
{
	t_line	line;
	char	input_str[100000];
	char	**exec_line;
	struct sigaction	act;
	
	child_pid = 0;
	act.sa_flags = 0;
	act.sa_handler = sighandler;
	sigaction(SIGINT, &act, NULL);

	init_line(&line);
	ft_bzero(input_str, 100000);
	while (TRUE)
	{
		take_input(input_str);
		//printf("Confirm input: %s\n", input_str);
		exec_line = parse_to_array(input_str);
		if (!exec_line)
		{
			printf("Error: not enough memory\n");
			break ;
		}
		parse_line_to_struct(&line, exec_line);
		free_array(exec_line);
		if (redirects(&line) == 2)
			break ;
	}
	return (0);
}