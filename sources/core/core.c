/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/06/26 20:22:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

char	ft_switch(t_line *line)
{
	t_func	*f;

	if (!ft_strcmp(line->command, "exit"))
		return (1);
	if (!line->command[0])
		return (0);
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/')
	{
		execute_file(line);
		return (0);
	}
	f = (t_func *)dict_get(&(line->func_dict), line->command);
	if (!f)
	{
		printf("'%s'\n", line->command);
		dict_set(&(line->env), ft_strdup("?"), ft_strdup("-7"));
		return (0);
	}
	f->foo(line);
	return (0);
}

void	sighandler(int sig)
{
	(void)sig;
	if (g_child_pid != 0)
	{
		kill(g_child_pid, SIGINT);
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

static void	clear_dicts(t_line *line)
{
	dict_del(&(line->env));
	dict_del(&(line->func_dict));
}

int	main(void)
{
	char	rotate;
	t_line	line;

	init_env(&line);
	func_dict_init(&line);
	init_struct(&line);
	g_child_pid = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
	rotate = 0;
	while (!rotate)
		rotate = process_input(&line);
	rl_clear_history();
	clear_dicts(&line);
	clear_struct(&line);
	return (0);
}
