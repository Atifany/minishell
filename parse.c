/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:01:28 by alex              #+#    #+#             */
/*   Updated: 2022/06/26 19:17:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static void	copy_symbol(void *arr, int i, int l, char str, int insquotes)
{
	if (!insquotes && str == '$')
		(((char **)(arr))[i])[l] = -50;
	else
		(((char **)(arr))[i])[l] = str;

}

static int	writer(char *input_str,	char **arr, t_list **env)
{
	int		i;
	int		j;
	int		l;
	char	c;
	char	**t;	

	i = 0;
	j = 0;
	l = 0;
	while (input_str[j] != 0)
	{
		t = &((char **)arr)[i];
		while (input_str[j] == ' ')
			j++;
		while (input_str[j] != ' ' && input_str[j] != 0)
		{	
			if (input_str[j] == '"' || input_str[j] == '\'')
			{
				c = input_str[j];
				while (++j && input_str[j] && input_str[j] != c)
					copy_symbol(arr, i, l++, input_str[j], c == '\'');
				j++;
				variable_handler(t, env);
			}
			else
				copy_symbol(arr, i, input_str[j++], 0);
		}
		variable_handler(t, env);
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
			else
				((int *)(arr))[i]++;
			j++;
		}
		while (input_str[j] == ' ')
			j++;
		i++; 
	}
	return i;
}

char	**parse_to_array(char *input_str, t_list **env)
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
	i = writer(input_str, arr, env);
	while (--i >= 0)
		arr[i] = arr[i] - len_arr[i];
	free(len_arr);


	return (arr);
}
