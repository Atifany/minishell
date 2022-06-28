#include "../_headers/minishell.h"

void	print_error(t_line *line)
{
	int		error;
	char	*errors[12];

	errors[0] = "";
	errors[1] = "pwd: too many arguments";
	errors[2] = "Error: getcwd() failed";
	errors[3] = "cd: too many arguments";
	errors[4] = "Error: specified path does not exist";
	errors[5] = "export: incorrect argument";
	errors[6] = "env: too many arguments";
	errors[7] = "command is not recognized";
	errors[8] = "Error: no such file or directory";
	errors[9] = "Warning: can not open file";
	errors[10] = "cat: no files specified";
	errors[11] = "unset: no files specified";
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
