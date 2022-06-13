#include "../_headers/minishell.h"

void len_arr_inc(void *len_arr, int i, char str)
{
	(void)str;
	str = 0;
	if (str != '\'')
		((int *)(len_arr))[i]++;
}

void copy_symbol(void *arr, int i, char str)
{
	*(((char **)(arr))[i]) = str;
	((char **)arr)[i]++;
}

int helper(char *input_str, void f(void *, int, char), void *arr)
{
	int		i = 0;
	int		j = 0;

	while (input_str[j] != 0)
	{
		while (input_str[j] == ' ')
			j++;
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"')
			{
				j++;
				while (input_str[j] != '"')//catch error of unclosed quotes here
					f(arr, i, input_str[j++]);
				j++;
			}
			else if (input_str[j] == '\'')
			{
				f(arr, i, input_str[j++]);
				while (input_str[j] != '\'')//catch error of unclosed quotes here
					f(arr, i, input_str[j++]);
				j++;
			}
			else
				f(arr, i, input_str[j++]);
		}
		i++; 
		if (input_str[j] != 0)
			j++;
	}
	return i;
}

char	**parse_to_array(char *input_str)
{
	char	**arr;
	int		*len_arr = ft_calloc(count(input_str, ' ') + 1, 8);

	int i = helper(input_str, *len_arr_inc, len_arr);	
	arr = malloc(8 * (i + 1));	
	arr[i] = NULL;
	while (--i >= 0)
		arr[i] = ft_calloc(len_arr[i] + 1, 1);	
	i = helper(input_str, *copy_symbol, arr);	
	while (--i >= 0)
		arr[i] = arr[i]-len_arr[i];
	free(len_arr);
	return (arr);
}
