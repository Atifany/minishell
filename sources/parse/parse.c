#include "../_headers/minishell.h"

static void	copy_symbol(char **arr, int *j, char *str, int insquotes)
{
	if (!insquotes && str[*j] == '$')
	{
		**arr = -37;
		(*arr)++;
		(*j)++;
		while (ft_isalnum(str[*j]) || str[*j] == '_')
		{
			**arr = -str[*j];	
			(*j)++;
			(*arr)++;
		}
		(*j)--;
	}
	else
	{
		**(arr) = str[*j];
		(*arr)++;	
	}
}
static int	writer(char *input_str,	char **arr)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (input_str[j] != 0)
	{
		while (input_str[j] == ' ')
			j++;
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"' || input_str[j] == '\'')
			{
				c = input_str[j];
				while (++j && input_str[j] && input_str[j] != c)
					copy_symbol(&(arr[i]), &j, input_str, c == '\'');
				j++;
			}
			else
			{
				copy_symbol(&(arr[i]), &j, input_str, 0);
				j++;
			}
		}
		while (input_str[j] == ' ')
			j++;
		i++;
	}
	return i;
}

static int	size_counter(char *input_str, int *arr)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (input_str[j] != 0)
	{
		while (input_str[j] == ' ')
			j++;
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"' || input_str[j] == '\'')
			{
				c = input_str[j];
				while (++j && input_str[j] && input_str[j] != c)
					((int *)(arr))[i]++;
				j++;
			}
			else{
				((int *)(arr))[i]++;
				j++;
			}
		}
		while (input_str[j] == ' ')
			j++;
		i++; 
	}
	return i;
}

char	**parse_to_array(char *input_str)
{
	char	**arr;
	int		*len_arr;
	int		i;

	len_arr = calloc(count(input_str, ' ') + 1, 8);
	i = size_counter(input_str, len_arr);
	arr = malloc(8 * (i + 1));
	arr[i] = NULL;
	while (--i >= 0)
		arr[i] = calloc(len_arr[i] + 1, 1);
	i = writer(input_str, arr);
	while (--i >= 0)
		arr[i] = arr[i] - len_arr[i];
	free(len_arr);	
	return (arr);
}
