# include <stdio.h>

int main(int argc, char **argv)
{
	int i = 1;

	if (argc != 2)
	{
		printf("Error: argument| %d is %s\n", argc, *argv);
		return (1);
	}
	printf("LOG: argument| %d is %s\n", argc, *argv);
	while (i <= argv[1][0] - '0')
	{
		printf("[%d]\ngit pull", i);
		i++;
	}
	return (0);
}