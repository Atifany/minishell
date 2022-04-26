/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:04:53 by atifany           #+#    #+#             */
/*   Updated: 2021/10/07 14:04:54 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	copier(char	**substr, size_t l, char const *s)
{
	*substr = (char *)ft_calloc(l, sizeof(char));
	if (*substr)
		ft_strlcpy(*substr, s, l);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)ft_calloc(1, sizeof(char));
		if (substr)
			ft_strlcpy(substr, "\0", 1);
		return (substr);
	}
	while (start-- > 0)
		s++;
	if (ft_strlen(s) >= len)
		copier(&substr, len + 1, s);
	else
		copier(&substr, ft_strlen(s) + 1, s);
	return (substr);
}
