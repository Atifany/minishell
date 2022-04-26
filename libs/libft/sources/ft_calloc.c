/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:01:50 by atifany           #+#    #+#             */
/*   Updated: 2021/10/07 13:01:51 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*array;

	array = malloc(count * size);
	if (array)
		ft_bzero(array, count * size);
	return ((void *)array);
}
