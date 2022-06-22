/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/06/22 13:28:20 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

char	ft_switch(t_line *line)
{
	if (!ft_strcmp(line->command, "exit"))
	{
		dict_set(&(line->env), "?", ft_strdup("0"));
		return (1);
	}
	if (!line->command[0])
		return 0; 
	
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/'){
		execute_file(line);
		return (0);
	}
	func *f = dict_get(&(line->func_dict), line->command);
	if (!f)
	{
		printf("'%s'\n", line->command);
		dict_set(&(line->env), "?", ft_strdup("-7"));
		return (0);
	}
	f->foo(line);
	return (0);
}

void	sighandler(int sig)
{
	(void)sig;
	if (child_pid != 0)
	{
		kill(child_pid, SIGINT);
		write(1, "\n", 1);
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

int	main()
{
	char	rotate;
	t_line	line;
	//t_list *env;
	//t_list *shell;

	func_dict_init(&(line.func_dict));
	child_pid = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);

	init_struct(&line);
	rotate = 0;
	while (!rotate)
	{
		rotate = process_input(&line);
	}
	clear_struct(&line);
	rl_clear_history();
	return (0);
}
