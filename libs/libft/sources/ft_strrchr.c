/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:04:19 by atifany           #+#    #+#             */
/*   Updated: 2021/10/26 16:04:20 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*target;

	target = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			target = (char *)s;
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	return (target);
}
