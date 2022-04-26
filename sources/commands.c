#include "../minishell.h"

char	execute_file(char *command, char **arguments)
{
	int child_id;
	int status;

	child_id = fork();
	if (child_id == -1)
		return (1);
	//child
	if (child_id == 0)
	{
		arguments[0] = arguments[0] + 2;
		execve(command, arguments, NULL);
		exit(0);
	}
	//parent
	else
		wait(&status);
	return (0);
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
