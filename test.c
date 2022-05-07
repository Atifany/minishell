# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>

int main(int argc, char **argv)
{
	int i = 0;

	printf("%x\n", RL_READLINE_VERSION);
	printf("I recieved: ");
	while (i < argc)
	{
		if (argv[0][0] == '.')
			sleep(1);
		printf("%s\n", argv[i++]);
	}
	printf("\n");
	/*i = 0;
	while (i < argc)
	{
		printf("[%s]\n", argv[i]);
		i++;
	}
	printf("\n");*/
	return (0);
}