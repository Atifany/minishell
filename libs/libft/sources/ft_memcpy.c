/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:36:24 by atifany           #+#    #+#             */
/*   Updated: 2021/10/06 18:36:25 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dstbuf;
	unsigned char		*dst1;
	const unsigned char	*src1;

	if (!dst && !src)
		return ((void *)0);
	dst1 = dst;
	src1 = src;
	dstbuf = dst;
	while (n > 0)
	{
		*dst1 = *src1;
		dst1++;
		src1++;
		n--;
	}
	return (dstbuf);
}
