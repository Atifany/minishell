# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include "minishell.h"

int main(int argc, char **argv)
{
	int i = 0;

	/*printf("FIRST ME!\n");
	printf("I recieved: ");
	while (i < argc)
	{
		if (argv[0][0] == '.')
			sleep(1);
		printf("%s\n", argv[i++]);
	}
	printf("\n");*/
	char buf[10];
	ft_bzero(buf, 10);
	int ret = 1;
	while (ret > 0){
		ret = read(0, &buf, 1);
		printf("%s", buf);
		ft_bzero(buf, 10);
	}
	return (0);
}