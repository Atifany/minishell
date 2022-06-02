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
	line->pip_in = NULL;
	line->pip_out = NULL;
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	line->command = NULL;
	line->args = NULL;
	line->fd_to_write = NULL;
	line->fd_to_read = NULL;
	line->is_appending = FALSE;
	line->env = NULL;
	line->shell = NULL;
}

char ft_switch(t_line *line)
{
	// If, for example, I enter "exi", ft_strncmp will consider it as "exit" command and execute it,
	// which is totaly incorrect!

	func *f = (func *)dict_get(&line->func_dict, "hw_func");
	if (!f)
	{
		printf("%s is not recognised as command\n", line->command);
		return 0;
	}
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/')
		execute_file(line->args);
	else if (!ft_strcmp(line->command, "exit"))
	{
		clear_struct(line);
		return (1);
	}
	printf("%s",f->foo(line));		
	return (0);
}

void	redirect_input(t_line *line, char *mode){
	static int	save_in_stream;

	if (!ft_strcmp(mode, "init")){
		save_in_stream = dup(STDIN_FILENO);
		line->pip_in = (int *)malloc(sizeof(int) * 2);
		pipe(line->pip_in);
	}
	else if (!ft_strcmp(mode, "open")){
		dup2(line->pip_in[READ], STDIN_FILENO);
	}
	else if (!ft_strcmp(mode, "close") && line->pip_in){
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

t_list *func_dict_init(void)
{
	t_list *func_dict;
	func_dict = NULL;

	func *pwd;
	pwd = malloc(sizeof(func));
	pwd->foo = execute_pwd;
	dict_set(&func_dict, "pwd", pwd);

	func *cd;
	cd = malloc(sizeof(func));
	cd->foo = execute_cd;
	dict_set(&func_dict, "cd", cd);

	func *echo;
	echo = malloc(sizeof(func));
	echo->foo = execute_echo;
	dict_set(&func_dict, "echo", echo);

	func *env;
	env = malloc(sizeof(func));
	env->foo = execute_env;
	dict_set(&func_dict, "env", env);

	func *export;
	export = malloc(sizeof(func));
	export->foo = execute_export;
	dict_set(&func_dict, "export", export);
}

int	main()
{
	char	is_pipe_in_opened = FALSE;
	char	rotate;
	char	**exec_line;
	t_line	line;
	char	input_str[100000];
	//struct sigaction	act;
	

	int		total_shift;	// represents total shift on exec_line
	int		shift;			// represents current cmd shift on exec_line

	line.func_dict = func_dict_init();
	child_pid = 0;
	//act.sa_flags = 0;
	//act.sa_handler = sighandler;
	//sigaction(SIGINT, &act, NULL);

	init_line(&line);
	ft_bzero(input_str, 100000);
	rotate = TRUE;
	while (rotate)
	{
		redirect_input(&line, "init");
		take_input(input_str);

		exec_line = parse_to_array(input_str);
		if (!exec_line){
			printf("Error: not enough memory\n");
			break ;
		}
		shift = 0;
		total_shift = 0;
		while (*exec_line){		// iterates each command in current line
			if (line.is_piping && !is_pipe_in_opened){
				is_pipe_in_opened = TRUE;
				redirect_input(&line, "open");
				//printf("Opened pipe_in!\n");
			}
			shift = parse_line_to_struct(&line, exec_line);
			total_shift += shift;
			exec_line += shift;
			if (!line.is_redirecting){
				if (ft_switch(&line))
					rotate = FALSE;
			}
			else{
				if (redirects(&line) == 2)
					rotate = FALSE;
			}
		}
		if (is_pipe_in_opened){
			redirect_input(&line, "close");
			//printf("Closed pipe_in!\n");
			is_pipe_in_opened = FALSE;
		}
		exec_line -= total_shift;
		free_array(exec_line);
	}
	return (0);
}