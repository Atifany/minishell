#include "../minishell.h"

char *dict_get(t_list **lst, char* key)
{
	while (*lst)
	{
		if (((kv *)(*lst)->content)->key == key)
			return ((kv *)(*lst)->content)->value;
		*lst = (*lst)->next;
	}
	return NULL;
}

void dict_add(t_list **lst, char* key, void* value)
{
	kv *kv;

	kv = malloc(16);
	kv->key = key;
	kv->value = value;
	ft_lstadd_back(lst, ft_lstnew(kv));
}

void dict_set(t_list **lst, char* key, void* value)
{
	t_list *start;

	start = *lst;
	while (*lst)
	{
		if (((kv *)(*lst)->content)->key == key)
		{
			((kv *)(*lst)->content)->value = value;
			*lst = start;
			return ;
		}
		*lst = (*lst)->next;
	}
	*lst = start;
	dict_add(lst, key, value);
}

void dict_del(t_list **lst, char* key, void (*del)(void *))
{
	t_list *start;
	t_list *lstnext;

	start  = *lst;
	while (*lst)
	{
		if ((*lst) && (*lst)->next && ((kv *)(*lst)->next->content)->key == key)
		{
			lstnext = (*lst)->next;
			(*lst)->next = NULL;
			ft_lstadd_back(lst, lstnext->next);		
			del(lstnext);
			*lst = start;
			return ;
		}
		*lst = (*lst)->next;
	}
	*lst = start;
}
