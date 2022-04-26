/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:54:29 by atifany           #+#    #+#             */
/*   Updated: 2021/10/22 13:54:30 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*buf;

	if (!*lst)
		return ;
	tmp = *lst;
	buf = tmp->next;
	while (buf)
	{
		ft_lstdelone(tmp, del);
		tmp = buf;
		buf = tmp->next;
	}
	ft_lstdelone(tmp, del);
	*lst = NULL;
}
