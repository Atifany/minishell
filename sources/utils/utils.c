#include "../_headers/minishell.h"

void	print_error(t_line *line)
{
	int		error;
	char	*errors[] = {"", "pwd: too many arguments",
	"Error: getcwd() failed",
	"cd: too many arguments",
	"Error: %s does not exist or there is not enough memory",
	"export: incorrect argument",
	"env: too many arguments",
	"command is not recognized",
	"Error: no such file or directory",
	"Warning: can not open file",
	"cat: no files specified"};

	error = ft_atoi(dict_get(&(line->env), "?"));
	if (error < 0)
		printf("%s\n", errors[-error]);
	else if (WIFSIGNALED(error))
		printf("Program killed by signal: %d\n", WTERMSIG(error));
	else
		dict_set(&(line->env), ft_strdup("?"), ft_itoa(WEXITSTATUS(error)));
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1)
		str1 = STR_EMPTY;
	if (!str2)
		str2 = STR_EMPTY;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	arr_len(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	count(char *arr, char s)
{
	int	c;

	c = 0;
	while (*arr)
	{
		if (*arr == s)
			c++;
		arr++;
	}
	return (c);
}

int	ft_to_positive(int n)
{
	if (n < 0)
		n = 0;
	return (n);
}
