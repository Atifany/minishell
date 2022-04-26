/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:56 by atifany           #+#    #+#             */
/*   Updated: 2021/10/22 14:25:57 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ans;
	t_list	*anspointer;

	if (lst)
	{
		ans = ft_lstnew(f(lst->content));
		if (!ans)
			return (NULL);
	}
	else
		return (NULL);
	anspointer = ans;
	while (lst->next)
	{
		lst = lst->next;
		ans->next = ft_lstnew(f(lst->content));
		if (!ans->next)
		{
			ft_lstclear(&anspointer, del);
			return (NULL);
		}
		ans = ans->next;
	}
	return (anspointer);
}
