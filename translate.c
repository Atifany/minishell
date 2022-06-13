# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int main(int argc, char **argv){
	char buf[2];
	buf[0] = 0;
	buf[1] = 0;

	int ret = read(0, &buf, 1);
	while (ret > 0 && buf[0] != 0){
		printf("%s", buf);
		ret = read(0, &buf, 1);
	}
}