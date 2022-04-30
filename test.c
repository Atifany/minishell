# include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;

	printf("I recieved: ");
	while (i < argc)
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
	return (0);
}