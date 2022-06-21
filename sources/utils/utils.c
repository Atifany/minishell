/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:16:41 by atifany           #+#    #+#             */
/*   Updated: 2022/06/21 21:44:03 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

int print_error(int error)
{
	char *errors[] = {"", "pwd: too many arguments",
	"Error: getcwd() failed",
	"cd: too many arguments",
	"Error: %s does not exist or there is not enough memory",
	"export: incorrect argument",
	"env: too many arguments",
	"command is not recognized",
	"no such file or directory"};

	if (error < 0)
		printf("%s\n", errors[-error]);
	else if (error == 127)
		printf("%s\n", errors[8]);	
	else if (error >= 0)
		printf("Programm exited with code: %d\n", error);
	
}

int	ft_strcmp(char *str1, char *str2){
	int	i;

	if (!str1)
		str1 = STR_EMPTY;
	if (!str2)
		str2 = STR_EMPTY;
	i = 0;
	while (str1[i] && str2[i]){
		if (str1[i] != str2[i]){
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (str1[i] - str2[i]);
}

int arr_len(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return i;
}

void	free_array(char **array)
{
	int	i;
	if (array == NULL)
		return ;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_struct_array(t_inqu **array)
{
	int	i;
	if (array == NULL)
		return ;

	i = 0;
	while (array[i])
	{
		free(array[i]->arg);
		free(array[i]);
		i++;
	}
	free(array);
}

int count(char *arr, char s)
{
	int c;

	c = 0;
	while (*arr)
	{
		if (*arr == s)
			c++;
		arr++;
	}
	return c;
}

int	ft_to_positive(int n)
{
	if (n < 0){
		n = 0;
	}
	return (n);
}
