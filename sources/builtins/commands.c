/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:33 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:22:34 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static int	public_execution(t_line *line, char	**paths)
{
	int		i;

	i = 0;
	if (execve(line->args[0], line->args, NULL) == 0)
		return (0);
	while (paths[i] && line->command[0] != '/')
	{
		paths[i] = gnl_join(&(paths[i]), "/", 1);
		paths[i] = gnl_join(&(paths[i]), line->command,
				ft_strlen(line->command));
		if (execve(paths[i], line->args, NULL) == 0)
			return (0);
		i++;
	}
	if (line->command[0] == '/')
		write(2, "Error: no such file\n", 21);
	else
	{
		write(2, line->command, ft_strlen(line->command));
		write(2, " command is not recognized\n", 28);
	}
	return (1);
}

int	execute_file(t_line *line)
{
	int		status;
	char	**paths;
	char	*status_to_pipe;

	signal(SIGINT, SIG_IGN);
	paths = ft_split(dict_get(&(line->env), "PATH"), ':');
	status = 0;
	g_child_pid = fork();
	if (g_child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (public_execution(line, paths))
			exit(1);
	}
	else
		wait(&status);
	status_to_pipe = ft_itoa(status);
	write(line->pip_status[WRITE],
		status_to_pipe, ft_strlen(status_to_pipe));
	free(status_to_pipe);
	g_child_pid = 0;
	free_array(paths);
	return (status);
}

static void	cd_spec_symbol_handler(t_line *line, char **path,
	char *prev_path)
{
	char	*buf1;
	char	*buf2;

	if (!line->args[1])
		*path = ft_strdup((char *)dict_get(&(line->env), "HOME"));
	else
	{
		if (*(line->args[1]) == '~')
		{
			buf1 = ft_strdup((char *)dict_get(&(line->env), "HOME"));
			buf2 = ft_strdup(line->args[1] + 1);
			*path = gnl_join(&buf1, buf2,
					ft_strlen(line->args[1] + 1));
			free(buf2);
		}
		else if (!ft_strcmp(line->args[1], "-"))
			*path = ft_strdup(prev_path);
		else
			*path = ft_strdup(line->args[1]);
	}
}

char	execute_cd(t_line *line)
{
	static char	*prev_path = NULL;
	int			dir;
	char		*path;

	if (line->args[1] && line->args[2])
	{
		write(2, "cd: too many args\n", 19);
		return (1);
	}
	if (!prev_path)
		prev_path = getcwd(NULL, 0);
	cd_spec_symbol_handler(line, &path, prev_path);
	free(prev_path);
	prev_path = getcwd(NULL, 0);
	dir = chdir(path);
	if (!ft_strcmp(line->args[1], "-"))
		printf("%s\n", path);
	free(path);
	if (dir == -1)
	{
		write(2, "cd: specified path not found\n", 30);
		return (1);
	}
	return (0);
}

char	execute_echo(t_line *line)
{
	char	nl_flag;
	char	**args;

	args = line->args + 1;
	nl_flag = '\n';
	if (!*args)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strcmp(args[0], "-n"))
	{
		args++;
		nl_flag = '\0';
	}
	while (*(args) && *(args + 1))
	{
		write(1, *args, ft_strlen(*args));
		write(1, " ", 1);
		args++;
	}
	write(1, *args, ft_strlen(*args));
	write(1, &nl_flag, 1);
	return (0);
}
