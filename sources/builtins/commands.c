#include "../_headers/minishell.h"


void	execute_file(t_line *line)
{
	int error;

	error = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(line->args[0], line->args, NULL) < 0)
			exit(127);
	}
	else
		wait(&error);
	
	child_pid = 0;

	if (WIFSIGNALED(error))
		return dict_set(&(line->env), ft_strdup("?"), ft_itoa(error));
	return dict_set(&(line->env), ft_strdup("?"), ft_itoa(WEXITSTATUS(error)));
}

void	execute_pwd(t_line *line)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-2"));
	printf("%s\n", buf);
	free(buf);
	return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
}

void	execute_cd(t_line *line)
{
	static char *prev_path = NULL;
	int			dir;
	char		*path;
	char		*buf;
	
	if (line->args[1] && line->args[2])
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-3"));
	if (!prev_path)
		prev_path = getcwd(NULL, 0);
	if (!line->args[1])
		path = ft_strdup((char *)dict_get(&(line->env), "HOME"));
	else
	{
		if (*(line->args[1]) == '~'){
			buf = ft_strdup((char *)dict_get(&(line->env), "HOME"));
			path = gnl_join(&buf, ft_strdup(line->args[1] + 1),
				ft_strlen(line->args[1] + 1));
		}
		else
			path = ft_strdup(line->args[1]);
	}
	if (!ft_strcmp(line->args[1], "-"))
		path = ft_strdup(prev_path);
	free(prev_path);
	prev_path = getcwd(NULL, 0);
	dir = chdir(path);
	if (!ft_strcmp(line->args[1], "-"))
		execute_pwd(line);
	free(path);
	if (dir == -1)
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-4"));
	return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
}

void	execute_echo(t_line *line)
{
	char nl_flag;
	char **args = line->args + 1;

	nl_flag = '\n';
	if (!*args){
		write(1, "\n", 1);
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
	}
	if (!ft_strcmp(args[0], "-n")){
		args++;
		nl_flag = '\0';
	}
	while (*(args) && *(args + 1)){
		write(1, *args, ft_strlen(*args));
		write(1, " ", 1);
		args++;
	}
	write(1, *args, ft_strlen(*args));
	write(1, &nl_flag, 1);
	return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
}

void	execute_env(t_line	*line)
{
	t_list *env;

	if (line->args[1])
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-6"));
	env = line->env; 
	while (env)
	{
		if (ft_strcmp((char *)((kv *)env->content)->key, "?"))
			printf("%s=%s\n", (char *)((kv *)env->content)->key, (char *)((kv *)env->content)->value);
		env = env->next;
	}
	return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
}

void	execute_export(t_line *line)// dobavit oshibku soderjit v imeni zapreshennie v rf simvoli
{
	int dir;
	char **t;
	int i;

	i = 0;	
	if ((line->args[1] && line->args[2])
		|| line->args[1] == NULL)
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5"));
	t = ft_split(line->args[1], '=');
	if (t[0] == NULL || t[1] == NULL)
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5"));
	while (line->args[1][i])
		if (!ft_isalnum(line->args[1][i]))
			return dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5"));
	dict_set(&(line->env), ft_strdup(t[0]), ft_strdup(t[1]));
	free_array(t);
	return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
}

void	execute_cat(t_line *line) // ADD ERROR AMANAGMENT
{
	int		i = 1;
	char	*str;
	int		fd;

	if (!line->args[0] || !line->args[1]){
		return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
	}
	while (line->args[i]){
		fd = open(line->args[i], O_CREAT | O_RDWR, 0666);
		if (fd < 0){
			return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
		}
		while (ft_cat(fd, &str) > 0){
			write(1, str, ft_strlen(str));
			free(str);
			str = NULL;
		}
		close(fd);
		i++;
	}
	return dict_set(&(line->env), ft_strdup("?"), ft_strdup("0"));
}
