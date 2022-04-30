/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:16:41 by atifany           #+#    #+#             */
/*   Updated: 2022/04/30 20:01:41 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_strj(char *s1, char *s2)
{
	char	*n;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	n = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!n)
		return (NULL);
	while (s1[i])
	{
		n[i] = s1[i];
		i++;
	}
	n[i++] = ' ';
	while (s2[j])
		n[i++] = s2[j++];
	n[i] = '\0';
	return (n);
}

int contains(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == '"')
			return '"';
		if (arr[i] == '\'')
			return '\'';
		i++;
	}
	return 0;
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

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return i;
}

char **dropnulls(char **arr, int len)
{
	int	i;
	int j;
	int newlen;

	newlen = 0;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (arr[i++] != NULL)
			newlen++;
	}
	char **newarr = malloc(8*(i+1));
	i = 0;
	while (i < len)
	{
		if (arr[i] != NULL)
		{
			newarr[j] = ft_strdup(arr[i]);
			free(arr[i]);
			j++;
		}
		i++;
	}
	free(arr);
	newarr[j] = NULL;
	return newarr;
}

void dropquotes(char **arr)
{
	int i = 0;
	int j = 0;
	int l = 0;
	char *t;

	while (arr[i])
	{
		j = 0;
		l = 0;
		t = malloc(ft_strlen(arr[i]) + 1);
		while (arr[i][j])
		{
			if (arr[i][j] == '"')
			{
				j++;
				while (arr[i][j] != '"')
					t[l++] = arr[i][j++];
				j++;
			}
			if (arr[i][j] == '\'')
			{
				j++;
				while (arr[i][j] != '\'')
					t[l++] = arr[i][j++];
				j++;
			}
			else
				t[l++] = arr[i][j++];
		}
		t[l] = '\0';
		free(arr[i]);
		arr[i] = t;
		i++;
	}
}