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
	else
		wait(NULL);
	child_pid = 0;
	return (TRUE);
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