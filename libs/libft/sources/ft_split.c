/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:12:02 by atifany           #+#    #+#             */
/*   Updated: 2021/10/08 16:12:03 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*clean_arr(char ***arr)
{
	int	i;

	i = 0;
	while (*arr[i] != NULL)
		free(*arr[i++]);
	free(*arr);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (++i && s[i - 1] != 0)
		if ((s[i] == c || s[i] == 0) && s[i - 1] != c)
			count++;
	return (count);
}

static char	**arr_fill(int words_count, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;
	char			**arr;

	i = 1;
	j = 0;
	start = 0;
	arr = ft_calloc(words_count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i - 1])
	{
		if ((s[i] == c || s[i] == 0) && s[i - 1] != c)
			arr[j++] = ft_substr(s, start, i - start);
		if (s[i] != c && s[i - 1] == c)
			start = i;
		if (j > 0 && !arr[j - 1])
			return (clean_arr(&arr));
		i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words_count;
	char	**arr;

	if (!s || ft_strlen(s) == 0)
	{
		arr = (char **)ft_calloc(1, sizeof(char *));
		if (arr)
			arr[0] = NULL;
		return (arr);
	}
	words_count = count_words(s, c);
	arr = arr_fill(words_count, s, c);
	if (!arr)
		return (NULL);
	arr[words_count] = NULL;
	return (arr);
}
