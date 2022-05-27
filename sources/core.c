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
	line->pip = NULL;
	line->command = NULL;
	line->args = NULL;
	line->fd_to_write = NULL;
	line->fd_to_read = NULL;
	line->is_appending = FALSE;
}

char ft_switch(t_line *line)
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
	}
	else if (!ft_strcmp(line->command, "echo")){
		execute_echo(line->args);
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

/*void	parse(char *input_str, t_line *line){

}*/

int	main()
{
	char	rotate;
	char	**exec_line;
	t_line	line;
	//t_list *env;
	//t_list *shell;
	char	input_str[100000];
	struct sigaction	act;
	int		total_shift;
	int		shift;	
	
	child_pid = 0;
	act.sa_flags = 0;
	act.sa_handler = sighandler;
	sigaction(SIGINT, &act, NULL);

	init_line(&line);
	ft_bzero(input_str, 100000);
	rotate = TRUE;
	while (rotate)
	{
		//parse(input_str, &line);
		take_input(input_str);

		exec_line = parse_to_array(input_str);
		if (!exec_line){
			printf("Error: not enough memory\n");
			break ;
		}
		shift = 0;
		total_shift = 0;
		while (*exec_line){
			shift = parse_line_to_struct(&line, exec_line);
			total_shift += shift;
			exec_line += shift;
			if (!*(line.fd_to_write) && !line.pip)
			{
				if (ft_switch(&line))
					rotate = FALSE;
			}
			else
				if (redirects(&line) == 2)
					rotate = FALSE;
		}
		exec_line -= total_shift;
		free_array(exec_line);
	}
	return (0);
}