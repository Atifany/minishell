/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:12 by atifany           #+#    #+#             */
/*   Updated: 2021/10/08 17:07:13 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ans_handler(int i, char *buf)
{
	char	*ans;

	ans = (char *)ft_calloc(12 - i, sizeof(char));
	if (ans)
		ft_strlcpy(ans, &buf[i], (12 - i) * sizeof(char));
	return (ans);
}

static void	negative_handler(char *is_neg, int n, long *n1)
{
	*is_neg = 0;
	*n1 = (long)n;
	if (*n1 < 0)
	{
		*is_neg = '-';
		*n1 *= -1;
	}
}

char	*ft_itoa(int n)
{
	char	buf[12];
	int		i;
	char	is_neg;
	long	n1;

	ft_bzero(buf, 12);
	buf[10] = '0';
	buf[11] = '\0';
	if (n == 0)
		return (ans_handler(10, buf));
	negative_handler(&is_neg, n, &n1);
	i = 10;
	while (n1 > 0)
	{
		buf[i--] = n1 % 10 + '0';
		n1 /= 10;
	}
	buf[i] = is_neg;
	if (buf[i] == 0)
		i += 1;
	return (ans_handler(i, buf));
}
