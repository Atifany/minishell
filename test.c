# include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;

	printf("I recieved: ");
	while (i <= argc);
		printf("%s\n", argv[i++]);
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