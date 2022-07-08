#include "sources/_headers/minishell.h"

int	main()
{
	int save_stdin;
	int pip1[2];
	int pip2[2];

	pipe(pip1);
	pipe(pip2);
	save_stdin = dup(STDIN_FILENO);

	write(pip1[WRITE], "AMONGUSUS\n", 10);
	write(pip2[WRITE], "ANONIMUSS\n", 10);
	close(pip1[WRITE]);
	close(pip2[WRITE]);

	if (fork())
	{
		dup2(pip1[READ], STDIN_FILENO);
		char	buf[1];
		int		i = 0;
		while (i < 10)
		{
			read(0, &buf, 1);
			write(1, buf, 1);
			i++;
		}
	}
	else
	{
		dup2(pip2[READ], STDIN_FILENO);
		char	buf[1];
		int		i = 0;
		while (i < 10)
		{
			read(0, &buf, 1);
			write(1, buf, 1);
			i++;
		}
		exit(0);
	}
	close(pip1[READ]);
	close(pip2[READ]);
	dup2(save_stdin, STDIN_FILENO);
}
