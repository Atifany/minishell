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
	{
		wait(&status);
	}
	return (TRUE);
}

void	print_dir(void)
{
	char	*buf;

	buf = NULL;
	printf("%s\n", getcwd(buf, 0));
	if (buf)
		free(buf);
}
