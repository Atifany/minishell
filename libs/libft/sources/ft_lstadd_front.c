/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:43:11 by atifany           #+#    #+#             */
/*   Updated: 2021/10/15 16:43:12 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
