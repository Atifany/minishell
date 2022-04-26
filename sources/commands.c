#include "../minishell.h"

char	execute_file(char *command)
{
	int child_id;
	int status;

	child_id = fork();
	if (child_id == -1)
		return (FALSE);
	//child
	if (child_id == 0)
	{
		execve(command, NULL, NULL);
		exit(0);
	}
	//parent
	else
	{
		wait(&status);
	}
	return (TRUE);
}
