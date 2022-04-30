#include "../minishell.h"

char	execute_file(char *command, char **arguments)
{
	int child_id;

	child_id = fork();
	if (child_id == -1)
		return (1);
	//child
	if (child_id == 0)
	{
		if (execve(command, arguments, NULL) < 0)
		{
			printf("Log: %s\n", command);
			printf("Error: invalid filename\n");
			exit(1);
		}
	}
	//parent
	else
		wait(NULL);
	return (TRUE);
}

char	print_dir(void)
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
