#include "../_headers/minishell.h"

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

char	is_in_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
