/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:49:56 by atifany           #+#    #+#             */
/*   Updated: 2021/10/05 18:49:57 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			k = i + 1;
			j = 1;
			while (k < len && haystack[k] == needle[j] && needle[j] && j++)
				k++;
			if (j == ft_strlen(needle))
				return ((char *)&(haystack[i]));
		}
		i++;
	}
	return (NULL);
}
