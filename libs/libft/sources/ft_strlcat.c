/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:25:56 by atifany           #+#    #+#             */
/*   Updated: 2021/10/06 17:25:58 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	i = ft_strlen(dst);
	j = 0;
	if (dstsize <= dst_len)
		return (dstsize + ft_strlen(src));
	while (i + 1 < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
	return (dst_len + ft_strlen(src));
}
