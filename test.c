#include "sources/_headers/minishell.h"

int main()
{
	int		pip[2];
	char	*buf;

	pipe(pip);
	write(pip[WRITE], "LOL KEK\n", 8);
	write(pip[WRITE], "\0\0\1\0\0", 4);
	close(pip[WRITE]);
	buf = get_next_line(pip[READ]);
	printf("%s", buf);
	buf += 8 + 1;
	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", buf[i]);
		//write(1, &(buf[i]), 1);
	}
	close(pip[READ]);
}