/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:16:02 by atifany           #+#    #+#             */
/*   Updated: 2021/10/13 14:16:03 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	negative_handler_helper(char *is_neg, int n, long *n1)
{
	*is_neg = 0;
	*n1 = (long)n;
	if (*n1 < 0)
	{
		*is_neg = '-';
		*n1 *= -1;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[11];
	int		i;
	char	is_neg;
	long	n1;

	if (n == 0)
		write(fd, "0", 1);
	negative_handler_helper(&is_neg, n, &n1);
	ft_bzero(buf, 11);
	i = 10;
	while (n1 > 0)
	{
		buf[i--] = n1 % 10 + '0';
		n1 /= 10;
	}
	buf[i] = is_neg;
	if (buf[i] == 0)
		i += 1;
	write(fd, &buf[i], 11 - i);
}
