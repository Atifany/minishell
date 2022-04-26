/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:52:15 by atifany           #+#    #+#             */
/*   Updated: 2021/10/07 13:52:15 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!s2)
		return (s2);
	ft_strlcpy(s2, s1, sizeof(char) * (ft_strlen(s1) + 1));
	return (s2);
}
