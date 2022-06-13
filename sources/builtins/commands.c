#include "../_headers/minishell.h"

char	execute_file(char **arguments)
{
	child_pid = fork();
	if (child_pid == -1)
		return (1);
	//child
	if (child_pid == 0)
	{
		if (execve(arguments[0], arguments + 1, NULL) < 0)
		{
			printf("Error: invalid filename\n");
			exit(1);
		}
	}
	//parent
	else{
		wait(NULL);
	}
	child_pid = 0;
	return (0);
}

char	*execute_pwd(t_line *line)
{
	char	*buf;

	if (line->args[1])
		return "pwd: too many arguments\n";
	buf = getcwd(NULL, 0);
	if (!buf)
		return ("Error: getcwd() failed\n");
	printf("%s\n", buf);
	free(buf);
	return (STR_EMPTY);
}

char	*execute_cd(t_line *line)
{
	int dir;
	char *path = line->args[1];
	
	if (line->args[1] && line->args[2])
		return ("cd: too many arguments\n");
	dir = chdir(path);
	if (dir == -1)
		return ("Error: %s does not exist or there is not enough memory\n");
	return (STR_EMPTY);
}

char	*execute_echo(t_line *line)
{
	char nl_flag;
	char **args = line->args + 1;

	nl_flag = '\n';
	if (!*args){
		printf("\n");
		return (STR_EMPTY);
	}
	if (!ft_strcmp(args[0], "-n")){
		args++;
		nl_flag = '\0';
	}
	while (*args){
		printf("%s ", *args);
		args++;
	}
	printf("%c", nl_flag);
	return (STR_EMPTY);
}

char	*execute_env(t_line	*line)
{
	t_list *env;

	env = line->env; 
	while (env)
	{
		printf("%s=%s\n", (char *)((kv *)env->content)->key, (char *)((kv *)env->content)->value);
		env = env->next;
	}
	return (STR_EMPTY);
}

char	*execute_export(t_line *line)
{
	char *key = line->args[1];
	dict_set(&(line->env), key, dict_get(&(line->shell), key));
	dict_del(&(line->shell), key);
	return (STR_EMPTY);
}

char	*execute_cat(t_line *line){
	int		i = 1;
	char	*str;
	int		fd;

	if (!line->args[0] || !line->args[1]){
		return (STR_EMPTY);
	}
	while (line->args[i]){
		fd = open(line->args[i], O_CREAT | O_RDWR, 0666);
		if (fd < 0){
			return (STR_EMPTY);
		}
		while (ft_cat(fd, &str) > 0){
			write(1, str, ft_strlen(str));
			free(str);
			str = NULL;
		}
		close(fd);
		i++;
	}
	return (0);
}
