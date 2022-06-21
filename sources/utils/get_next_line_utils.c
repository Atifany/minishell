/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:01:53 by atifany           #+#    #+#             */
/*   Updated: 2022/06/21 17:45:58 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/get_next_line.h"

size_t	gnl_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
		i++;
	return (i);
}

static void	*free_origin(char **ans)
{
	if (*ans)
	{
		free(*ans);
		*ans = NULL;
	}
	return (NULL);
}

# include <stdio.h>

char	*gnl_join(char **ans, char *buf, size_t count)
{
	char	*ans_cpy;
	size_t	ans_len;
	size_t	i_gen;
	size_t	i_cpy;

	ans_len = gnl_ft_strlen(*ans);
	ans_cpy = (char *)malloc(ans_len + count + 1);
	if (!ans_cpy)
		return (free_origin(ans));
	i_cpy = 0;
	while (i_cpy < ans_len)
	{
		ans_cpy[i_cpy] = (*ans)[i_cpy];
		i_cpy++;
	}
	i_gen = 0;
	while (i_gen < count)
		ans_cpy[i_cpy++] = (buf)[i_gen++];
	ans_cpy[i_cpy] = 0;
	free_origin(ans);
	return (ans_cpy);
}
