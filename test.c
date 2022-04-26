# include <stdio.h>

int main(int argc, char **argv)
{
	int i = 1;

	if (argc != 1)
	{
		printf("Error: argument| %d is %s\n", argc, *argv);
		return (1);
	}
	printf("LOG: argument| %d is %s\n", argc, *argv);
	while (i <= argv[0][0] - '0')
	{
		printf("[%d]\n", i);
		i++;
	}
	return (0);
}