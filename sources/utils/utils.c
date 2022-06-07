/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:16:41 by atifany           #+#    #+#             */
/*   Updated: 2022/05/02 17:32:53 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

int	ft_strcmp(char *str1, char *str2){
	int	i;

	i = 0;
	while (str1[i] && str2[i]){
		if (str1[i] != str2[i]){
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (str1[i] - str2[i]);
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
