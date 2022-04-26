/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:44:32 by atifany           #+#    #+#             */
/*   Updated: 2021/10/07 14:44:33 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	ans = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (ans)
	{
		ft_strlcpy(ans, s1, ft_strlen(s1) + 1);
		ft_strlcat(ans, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	return (ans);
}
