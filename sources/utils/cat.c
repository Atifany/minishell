#include "../_headers/minishell.h"

int	ft_cat(int fd, char **str_ptr)
{
	int		ret;
	char	buf[READ_BUFFER_SIZE + 1];

	ft_bzero(buf, READ_BUFFER_SIZE + 1);
	ret = read(fd, &buf, READ_BUFFER_SIZE);
	if (ret > 0)
		*str_ptr = ft_strdup(buf);
	return (ret);
}
