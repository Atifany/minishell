/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:20:12 by alex              #+#    #+#             */
/*   Updated: 2022/07/06 14:20:21 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static int	execute(char *path, char *argv[])
{
	g_child_pid = fork();
	if (!g_child_pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, argv, NULL);
		write(2, "Error: file was found, but can not be executed\n", 54);
		exit(1);
	}
	return (0);
}

static int	find_exe(t_line *line, char	**paths)
{
	int		i;

	i = 0;
	if (!access(line->args[0], 1))
		return (execute(line->args[0], line->args));
	while (paths[i] && line->command[0] != '/')
	{
		paths[i] = gnl_join(&(paths[i]), "/", 1);
		paths[i] = gnl_join(&(paths[i]), line->command,
				ft_strlen(line->command));
		if (!access(paths[i], 1))
			return (execute(paths[i], line->args));
		i++;
	}
	if (line->command[0] == '/')
		write(2, "Error: no such file\n", 21);
	else
	{
		write(2, line->command, ft_strlen(line->command));
		write(2, " command is not recognized\n", 28);
	}
	return (256);
}

int	execute_file(t_line *line)
{
	int		status;
	char	**paths;
	char	*status_to_pipe;

	signal(SIGINT, SIG_IGN);
	paths = ft_split(dict_get(&(line->env), "PATH"), ':');
	status = find_exe(line, paths);
	if (!status)
		wait(&status);
	status_to_pipe = ft_itoa(status);
	write(line->pip_status[WRITE],
		status_to_pipe, ft_strlen(status_to_pipe));
	free(status_to_pipe);
	g_child_pid = 0;
	free_array(paths);
	return (status);
}
