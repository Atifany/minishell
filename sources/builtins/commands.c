#include "../_headers/minishell.h"

static int	public_execution(t_line *line, char	**paths, int pip[2])
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
	printf("'%s'\n", line->command + 1);
	if (line->command[0] == '/')
		write(pip[WRITE], "-8", 2);
	else
		write(pip[WRITE], "-7", 2);
	return (1);
}

void	execute_file(t_line *line)
{
	char	buf[4];
	int		error;
	int		pip[2];
	char	**paths;

	paths = ft_split(dict_get(&(line->env), "PATH"), ':');
	error = 0;
	pipe(pip);
	g_child_pid = fork();
	if (g_child_pid == 0)
	{
		if (public_execution(line, paths, pip))
			exit(1);
	}
	else
		wait(&error);
	g_child_pid = 0;
	write(pip[WRITE], "\0\0", 2);
	read(pip[READ], &buf, 2);
	close(pip[READ]);
	close(pip[WRITE]);
	free_array(paths);
	if (*buf)
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup(buf)));
	return (dict_set(&(line->env), ft_strdup("?"), ft_itoa(error)));
}

static void	cd_spec_symbol_handler(t_line *line, char **path,
	char *prev_path)
{
	char	*buf1;
	char	*buf2;

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

void	execute_cd(t_line *line)
{
	static char	*prev_path = NULL;
	int			dir;
	char		*path;

	if (line->args[1] && line->args[2])
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-3")));
	if (!prev_path)
		prev_path = getcwd(NULL, 0);
	if (!line->args[1])
		path = ft_strdup((char *)dict_get(&(line->env), "HOME"));
	else
		cd_spec_symbol_handler(line, &path, prev_path);
	free(prev_path);
	prev_path = getcwd(NULL, 0);
	dir = chdir(path);
	if (!ft_strcmp(line->args[1], "-"))
		execute_pwd(line);
	free(path);
	if (dir == -1)
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-4")));
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}

void	execute_echo(t_line *line)
{
	char	nl_flag;
	char	**args;

	args = line->args + 1;
	nl_flag = '\n';
	if (!*args)
	{
		write(1, "\n", 1);
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
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
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}
