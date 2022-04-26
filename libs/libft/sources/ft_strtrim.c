/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:53:02 by atifany           #+#    #+#             */
/*   Updated: 2021/10/07 14:53:03 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	checker(unsigned char a, char const *set)
{
	while (*set)
		if (*set++ == a)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*buf;
	size_t	target;

	if (!s1)
		return (NULL);
	if (!set || !*set)
		return ((char *)ft_strdup(s1));
	buf = (char *)s1;
	while (*s1 && checker((unsigned char)*s1, set))
	{
		if (checker((unsigned char)*s1, set))
			buf = (char *)++s1;
		else
			++s1;
	}
	target = 0;
	if (ft_strlen(buf) != 0)
		target = ft_strlen(buf) - 1;
	while (target > 0 && checker(buf[target], set))
		target--;
	return (ft_substr(buf, 0, ++target));
}
