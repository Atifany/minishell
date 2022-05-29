# include "minishell.h"

int main(int argc, char **argv){
	int ret;
	char	buf[2];
	buf[0] = 0;
	buf[1] = 0;
	int		pip[2];
	pid_t	child_id;
	//int		save_out_stream;
	int		save_in_stream;

	//save_out_stream = dup(STDOUT_FILENO);
	save_in_stream = dup(STDIN_FILENO);

	if (pipe(pip) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	// 1
	int fd = open(argv[1], O_RDWR);

	ret = read(fd, &buf, 1);
	while (ret > 0 && buf[0] != 0){
		write(pip[WRITE], buf, 1);
		usleep(10000); // 1/100 a second
		ret = read(fd, &buf, 1);
	}
	close(pip[WRITE]);

	dup2(pip[READ], STDIN_FILENO);
	ret = read(STDIN_FILENO, &buf, 1);
	while (ret > 0 && buf[0] != 0){
		printf("%s", buf);
		ret = read(STDIN_FILENO, &buf, 1);
	}

	// 2
	fd = open(argv[1], O_RDWR);

	ret = read(fd, &buf, 1);
	while (ret > 0 && buf[0] != 0){
		write(pip[WRITE], buf, 1);
		usleep(10000); // 1/100 a second
		ret = read(fd, &buf, 1);
	}
	close(pip[WRITE]);

	dup2(pip[READ], STDIN_FILENO);
	ret = read(STDIN_FILENO, &buf, 1);
	while (ret > 0 && buf[0] != 0){
		printf("%s", buf);
		ret = read(STDIN_FILENO, &buf, 1);
	}
	dup2(save_in_stream, STDIN_FILENO);
	close(pip[READ]);
}