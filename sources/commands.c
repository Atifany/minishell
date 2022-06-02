#include "../minishell.h"

char	execute_file(char *command, char **arguments)
{
	child_pid = fork();
	if (child_pid == -1)
		return (1);
	//child
	if (child_pid == 0)
	{
		if (execve(command, arguments, NULL) < 0)
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

char	execute_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}

char	execute_cd(char *path)
{
	int dir;
	
	dir = chdir(path);
	if (dir == -1)
		return (1);
	return (0);
}

char	execute_echo(char **args){
	char nl_flag;

	nl_flag = '\n';
	if (!args){
		printf("\n");
		return (0);
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
	return (0);
}

void execute_env(t_list *env)
{
	while (env)
	{
		printf("%s=%s\n", ((kv *)env->content)->key, ((kv *)env->content)->value);
		env = env->next;
	}
}

void execute_export(t_list **env, t_list **shell, char* key)
{
	dict_set(env, key, dict_get(shell, key));
	dict_del(shell, key);
}

char	execute_cat(t_line *line){
	int i = 1;
	char	*str;
	int fd;

	if (!line->args[0] || !line->args[1]){
		printf("cat: no file sprecified\n");
		return (0);
	}
	while (line->args[i]){
		fd = open(line->args[i], O_CREAT | O_RDWR, 0666);
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