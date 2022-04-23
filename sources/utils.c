/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:16:41 by atifany           #+#    #+#             */
/*   Updated: 2022/04/23 16:16:42 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_dir(void)
{
	char	*buf;

	buf = NULL;
	printf("%s\n", getcwd(buf, 0));
	if (buf)
		free(buf);
}

void	ft_bzero(char *str, size_t bytes)
{
	while (bytes-- > 0)
		*(str++) = 0;
}

size_t	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen((char *)src));
	src_size = ft_strlen((char *)src);
	while (i + 1 < dstsize && i < src_size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen((char *)src));
}

