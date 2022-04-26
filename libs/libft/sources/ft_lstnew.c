/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:09:28 by atifany           #+#    #+#             */
/*   Updated: 2021/10/15 16:09:29 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = ft_calloc(1, sizeof(content) + sizeof(char *));
	if (elem)
	{
		elem->content = content;
		elem->next = NULL;
	}
	return (elem);
}
