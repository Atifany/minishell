#include "sources/_headers/minishell.h"

int	main()
{
	while (TRUE)
	{
		printf("lol\n");
		//write(1, "lol\n", 4);
		write(2, "kek\n", 4);
		usleep(1000000);
	}
	return (0);
}
