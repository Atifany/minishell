/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:35 by atifany           #+#    #+#             */
/*   Updated: 2022/07/08 13:05:24 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

int	ft_switch(t_line *line)
{
	t_func	*f;

	if (!line->command[0])
		return (0);
	f = (t_func *)dict_get(&(line->func_dict), line->command);
	if (!f)
		return (execute_file(line));
	else
		return (f->foo(line));
	return (0);
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
	init_streams(&line);
	init_struct(&line);
	g_child_pid = 0;
	rotate = 0;
	while (!rotate)
		rotate = process_input(&line);
	rl_clear_history();
	clear_dicts(&line);
	clear_struct(&line);
	clear_pips(&line);
	return (line.shell_exit_status);
}
