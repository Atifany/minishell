#include "../_headers/get_next_line.h"

static void	zero_fill(char **buf, short call_return)
{
	size_t	i;

	if (call_return == 1)
		while (**buf != 0)
			--(*buf);
	i = 0;
	while (i < BUFFER_SIZE + 2)
		(*buf)[i++] = 0;
}

static short	destroy_buf(char **buf)
{
	zero_fill(buf, 1);
	free(*buf);
	*buf = NULL;
	return (1);
}

static short	body(char **buf, char **ans)
{
	size_t	i;

	i = 1;
	while ((*buf)[i] != '\n' && (*buf)[i] != 0 && i < BUFFER_SIZE)
		i++;
	if ((*buf)[i] == '\n')
	{
		*ans = gnl_join(ans, *buf + 1, i);
		if (!*ans)
			return (destroy_buf(buf));
		if ((*buf)[i + 1] != 0)
			*buf += i;
		else
			zero_fill(buf, 1);
		return (1);
	}
	*ans = gnl_join(ans, *buf + 1, gnl_ft_strlen(*buf + 1));
	if (!*ans)
		return (destroy_buf(buf));
	zero_fill(buf, 1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*ans;
	short		flag;

	ans = NULL;
	flag = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buf)
	{
		buf = (char *)malloc(BUFFER_SIZE + 2);
		if (!buf)
			return (NULL);
		zero_fill(&buf, 0);
	}
	while (flag == 0)
	{
		if (buf[0] == 0 && buf[1] == 0 && read(fd, buf + 1, BUFFER_SIZE) < 1)
		{
			destroy_buf(&buf);
			return (ans);
		}
		flag = body(&buf, &ans);
	}
	return (ans);
}
