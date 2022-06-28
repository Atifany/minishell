#include "../_headers/minishell.h"

void	execute_file(t_line *line)
{
	char	buf[2];
	int		error;
	int		pip[2];

	error = 0;
	pipe(pip);
	g_child_pid = fork();
	write(pip[WRITE], "\0", 1);
	if (g_child_pid == 0)
	{
		if (execve(line->args[0], line->args, NULL) < 0)
			exit(write(pip[WRITE], "1", 1));
	}
	else
		wait(&error);
	g_child_pid = 0;
	read(pip[READ], &buf, 1);
	close(pip[READ]);
	close(pip[WRITE]);
	if (*buf)
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-8")));
	return (dict_set(&(line->env), ft_strdup("?"), ft_itoa(error)));
}

static void	cd_spec_symbol_handler(t_line *line, char **path,
	char *prev_path)
{
	char	*buf;

	if (*(line->args[1]) == '~')
	{
		buf = ft_strdup((char *)dict_get(&(line->env), "HOME"));
		*path = gnl_join(&buf, ft_strdup(line->args[1] + 1),
				ft_strlen(line->args[1] + 1));
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
