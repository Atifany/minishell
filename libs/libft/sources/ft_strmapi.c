/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:37:05 by atifany           #+#    #+#             */
/*   Updated: 2021/10/11 17:37:06 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ans;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ans = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!ans)
		return (NULL);
	while (s[i] != 0)
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	return (ans);
}
