# include "minishell.h"

int main(int argc, char **argv){
	char	buf[2];
	buf[0] = 0;
	buf[1] = 0;
	int		pip[2];
	pid_t	child_id;
	int		save_out_stream;

	if (pipe(pip) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	
	int fd = open(argv[1], O_RDWR);

	int ret = read(fd, &buf, 1);
	while (ret > 0 && buf[0] != 0){
		write(pip[WRITE], buf, 1);
		usleep(10000); // 1/100 a second
		ret = read(fd, &buf, 1);
	}
	close(pip[WRITE]);

	ret = read(pip[READ], &buf, 1);
	while (ret > 0 && buf[0] != 0){
		printf("%s", buf);
		ret = read(pip[READ], &buf, 1);
	}
	close(pip[READ]);
}