/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/05/27 17:40:40 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*take_input()
{
	char	*buf;

	buf = readline("\e[0;36mminishell \e[1;36m>> \e[0m");
	return (buf);
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

static void	init_struct(t_line *line)
{
	line->pip_in = NULL;
	line->pip_out = NULL;
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	line->command = NULL;
	line->args = NULL;
	line->fd_to_write = NULL;
	line->fd_to_read = NULL;
	line->fd_to_appwrite = NULL;
	line->fd_to_appread = NULL;
	line->is_appending = FALSE;
}

// char	run(t_line *line, char (*f)(char *)){
// 	return (f(line->args[0]));
// }

char	ft_switch(t_line *line)
{
	// If, for example, I enter "exi", ft_strncmp will consider it as "exit" command and execute it,
	// which is totaly incorrect!
	if (!line->command)
		return (0);
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/')
	{
		// put program name to the args list
		// extract program name from the full path argument
		execute_file(line->command, line->args);
	}
	else if (!ft_strcmp(line->command, "pwd"))
	{
		if (line->args[0]){
			printf("pwd: too many arguments\n");
			return (0);
		}
		if (execute_pwd())
			printf("Error: getcwd() failed\n");
	}
	else if (!ft_strcmp(line->command, "cd"))
	{
		if (line->args[0] && line->args[1]){
			printf("cd: too many arguments\n");
			return (0);
		}
		if (execute_cd(line->args[0]))
			printf("Error: %s does not exist or there is not enough memory\n", line->args[0]);
		// printf("uwu\n");
		// run(line, dict_get(&line->cmds, line->command));
		// printf("keks\n");
	}
	else if (!ft_strcmp(line->command, "echo")){
		execute_echo(line->args);
	}
	else if (!ft_strcmp(line->command, "cat")){
		execute_cat(line);
	}
	else if (!ft_strcmp(line->command, "exit"))
	{
		clear_struct(line);
		return (1);
	}
	else
		printf("%s is not recognised as command\n", line->command);
	return (0);
}

void	redirect_input(t_line *line, char mode){
	static int	save_in_stream;

	if (mode == INIT){
		save_in_stream = dup(STDIN_FILENO);
		line->pip_in = (int *)malloc(sizeof(int) * 2);
		pipe(line->pip_in);
	}
	else if (mode == OPEN){
		dup2(line->pip_in[READ], STDIN_FILENO);
	}
	else if (mode == CLOSE && line->pip_in){
		close(line->pip_in[READ]);
		close(line->pip_in[WRITE]);
		dup2(save_in_stream, STDIN_FILENO);
		free(line->pip_in);
		line->pip_in = NULL;
	}
}

void	sighandler(int sig)
{
	if (child_pid != 0)
	{
		printf("kill child\n");
		kill(child_pid, SIGINT);
		write(1, "\n", 1);
	}
	sig = 0;
}

void	init_commands(t_line *line){
	line->cmds = NULL;
	dict_set(&line->cmds, "cd", &execute_cd);
}

int	open_pipe_in_and_parse(t_line *line, char **exec_line, char mode){
	static char	is_pipe_in_opened = FALSE;
	char		is_open_queued = FALSE;
	int 		shift = 0;

	if (mode == OPEN){
		if (line->is_piping && !is_pipe_in_opened){
			is_open_queued = TRUE;
		}
		shift = parse_line_to_struct(line, exec_line);
		if ((*(line->fd_to_read) || *(line->fd_to_appread) || is_open_queued)
			&& !is_pipe_in_opened){
			is_pipe_in_opened = TRUE;
			redirect_input(line, OPEN);
		}
		is_open_queued = FALSE;
	}
	else{
		if (is_pipe_in_opened){
			redirect_input(line, CLOSE);
			is_pipe_in_opened = FALSE;
		}
	}
	return (shift);
}

void cat_to_pipe_in(t_line *line){
	char	*str;
	int		i = 0;
	int		fd;

	while (line->fd_to_read[i]){
		fd = open(line->fd_to_read[i], O_CREAT | O_RDWR, 0666);
		while (ft_cat(fd, &str) > 0){
			write(line->pip_in[WRITE], str, ft_strlen(str));
			free(str);
			str = NULL;
		}
		close(fd);
		i++;
	}
}

char	iterate_exec_line(char **exec_line, t_line *line){
	char	ret;
	int		total_shift;	// represents total shift on exec_line
	int		shift;			// represents current cmd shift on exec_line

	shift = 0;
	total_shift = 0;
	while (*exec_line){		// iterates each command in current line
		shift = open_pipe_in_and_parse(line, exec_line, OPEN);
		if (*(line->fd_to_read) || *(line->fd_to_appread)){
			cat_to_pipe_in(line);
		}
		if (line->pip_in){
			write(line->pip_in[WRITE], "\0", 1);
		}
		total_shift += shift;
		exec_line += shift;
		if (line->is_redirecting){
			redirect_output(line, "open");
		}
		ret = ft_switch(line);
		if (line->is_redirecting){
			redirect_output(line, "close");
		}
		if (ret) // switch returned exit code.
			return (1);
	}
	exec_line -= total_shift;
	open_pipe_in_and_parse(line, exec_line, CLOSE);
	return (0);
}

// move everything out of main!!!!
int	main()
{
	char	rotate;
	char	**exec_line;
	t_line	line;
	//t_list *env;
	//t_list *shell;
	char	*input_str = NULL;
	struct sigaction	act;
	
	child_pid = 0;
	act.sa_flags = 0;
	act.sa_handler = sighandler;
	sigaction(SIGINT, &act, NULL);

	//init_commands(&line);
	//init_struct(&line, "first");
	rotate = 0;
	while (!rotate)
	{
		init_struct(&line); // I guess it leaks, so add free() inside this func
		redirect_input(&line, INIT);
		input_str = take_input();
		exec_line = parse_to_array(input_str);
		free(input_str);
		input_str = NULL;
		if (!exec_line){
			printf("Error: not enough memory\n");
			break ;
		}
		rotate = iterate_exec_line(exec_line, &line);
		free_array(exec_line);
	}
	return (0);
}