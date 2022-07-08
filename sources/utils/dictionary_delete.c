/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:23:02 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:23:03 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

void	dict_del(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free(((t_kv *)(*lst)->content)->value);
		free(((t_kv *)(*lst)->content)->key);
		free((*lst)->content);
		free((*lst));
		*lst = next;
	}
}

static void	hznahuyafunc(t_list **start, t_list *next, t_list *prev)
{
	if (next)
	{
		if (prev)
			prev->next = next;
		else
			*start = next;
	}
	else if (prev)
		prev->next = NULL;
}

void	dict_delone(t_list **lst, char *key)
{
	t_list	*start;
	t_list	*prev;
	t_list	*del;
	t_list	*next;

	start = *lst;
	prev = NULL;
	del = NULL;
	next = NULL;
	while (lst && ft_strcmp(((t_kv *)(*lst)->content)->key, key))
	{
		if ((*lst)->next
			&& !ft_strcmp(((t_kv *)(*lst)->next->content)->key, key))
			prev = *lst;
		*lst = (*lst)->next;
	}
	del = *lst;
	if (del)
	{
		next = del->next;
		del->next = NULL;
		dict_del(&del);
	}
	hznahuyafunc(&start, next, prev);
	*lst = start;
}
