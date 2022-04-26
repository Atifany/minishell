/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:43:23 by atifany           #+#    #+#             */
/*   Updated: 2021/10/07 12:43:24 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstbuf;
	unsigned char	*srcbuf;

	dstbuf = dst;
	srcbuf = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (src < dst && dst < src + len)
	{
		while (len-- > 0)
			dstbuf[len] = srcbuf[len];
		return (dst);
	}
	while (len-- > 0)
		*dstbuf++ = *srcbuf++;
	return (dst);
}
