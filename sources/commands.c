#include "../minishell.h"

char	execute_file(char *command, char **arguments)
{
	int child_id;
	int status;

	child_id = fork();
	if (child_id == -1)
		return (FALSE);
	//child
	if (child_id == 0)
	{
		execve(command, arguments, NULL);
		exit(0);
	}
	//parent
	else
		wait(&status);
	return (TRUE);
}

char	print_dir(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (FALSE);
	printf("%s\n", buf);
	free(buf);
	return (TRUE);
}

char	execute_cd(char *path)
{
	DIR *dir;
	dir = opendir(path);
	if (!dir)
		return (FALSE);//Omega LUL
	return (TRUE);
}
