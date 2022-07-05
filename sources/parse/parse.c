/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:55 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:22:56 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static void	copy_symbol(char **arr, int *j, char *str, int insquotes)
{
	if (!insquotes && str[*j] == '$')
	{
		**arr = -37;
		(*arr)++;
		(*j)++;
		while (ft_isalnum(str[*j]) || str[*j] == '_' || str[*j] == '?')
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

static void	skip_spaces(char *input_str, int *j)
{
	while (input_str[*j] == ' ')
		(*j)++;
}

static void	writer(char *input_str,	char **arr, int *i)
{
	int		j;
	char	c;

	*i = 0;
	j = 0;
	while (input_str[j] != 0)
	{
		skip_spaces(input_str, &j);
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"' || input_str[j] == '\'')
			{
				c = input_str[j];
				while (++j && input_str[j] && input_str[j] != c)
					copy_symbol(&(arr[*i]), &j, input_str, c == '\'');
			}
			else
				copy_symbol(&(arr[*i]), &j, input_str, 0);
			if (input_str[j])
				j++;
		}
		skip_spaces(input_str, &j);
		(*i)++;
	}
}

static void	size_counter(char *input_str, int *arr, int *i)
{
	int		j;
	char	c;

	*i = 0;
	j = 0;
	while (input_str[j] != 0)
	{
		skip_spaces(input_str, &j);
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"' || input_str[j] == '\'')
			{
				c = input_str[j];
				while (++j && input_str[j] && input_str[j] != c)
					((int *)(arr))[*i]++;
			}
			else
				((int *)(arr))[*i]++;
			if (input_str[j])
				j++;
		}
		skip_spaces(input_str, &j);
		(*i)++;
	}
}

char	**parse_to_array(char *input_str)
{
	char	**arr;
	int		*len_arr;
	int		i;

	i = 0;
	len_arr = calloc(count(input_str, ' ') + 1, 8);
	size_counter(input_str, len_arr, &i);
	arr = malloc(8 * (i + 1));
	arr[i] = NULL;
	while (--i >= 0)
		arr[i] = calloc(len_arr[i] + 10, 1);
	writer(input_str, arr, &i);
	while (--i >= 0)
		arr[i] = arr[i] - len_arr[i];
	free(len_arr);
	return (arr);
}
