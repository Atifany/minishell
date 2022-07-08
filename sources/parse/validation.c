#include "../_headers/minishell.h"

static int	is_pipe(char *str)
{
	if (ft_strcmp(str, "|"))
		return (1);
	return ((0));
}

static int	is_redir(char *str)
{
	if (ft_strcmp(str, ">>"))
		return (1);
	if (ft_strcmp(str, ">"))
		return (1);
	if (ft_strcmp(str, "<<"))
		return (1);
	if (ft_strcmp(str, "<"))
		return (1);
	return (0);
}

int	validate(t_line *line)
{
	int	i;

	i = 0;
	while (line->args[i])
	{
		if (is_redir(line->args[i]) && (is_redir(line->args[i + 1])
				|| !line->args[i + 1] || is_pipe(line->args[i + 1])))
			return (1);
		else if (is_pipe(line->args[i]) && (is_pipe(line->args[i + 1])
				|| !line->args[i + 1] || i == 0))
			return (1);
	}
	return (0);
}
