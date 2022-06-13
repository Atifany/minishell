# include "sources/_headers/minishell.h"

int main(int argc, char **argv){
	if (argc == 1){
		printf("no file\n");
		return (1);
	}
	int fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
	int i = READ_BUFFER_SIZE * 2 - 1;
	while (i--){
		write(fd, "=", 1);
	}
	write(fd, "\0" , 1);
	close(fd);
	printf("finished\n");
	return (0);
}