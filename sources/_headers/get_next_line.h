#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1024
# include <unistd.h>
# include <stdlib.h>

char	*gnl_join(char **ans, char *buf, size_t count);
size_t	gnl_ft_strlen(char *s);
char	*get_next_line(int fd);

#endif
