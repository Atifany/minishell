#include "../_headers/minishell.h"

void *dict_get(t_list **lst, char* key)
{
	t_list *start;

	start = *lst;
	while (start != NULL)
	{
		if (!ft_strcmp(((kv *)(start)->content)->key, key))
			return ((kv *)(start)->content)->value;
		start = (start)->next;
	}
	return NULL;
}

// void *dict_show_values(t_list **lst, char* key)
// {
// 	t_list *start;

// 	start = *lst;
// 	while (*lst)
// 	{
// 		printf("%p\n", ((func *)(((kv *)(*lst)->content)->value))->foo);
// 		*lst = (*lst)->next;
// 	}
// 	*lst = start;
// 	return NULL;
// }

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
		if (!ft_strcmp(((kv *)(*lst)->content)->key, key))
		{
			free(((kv *)(*lst)->content)->value);
			((kv *)(*lst)->content)->value = value;
			*lst = start;
			return ;
		}
		*lst = (*lst)->next;
	}
	*lst = start;
	dict_add(lst, key, value);
}

void dict_del(t_list **lst, char* key/*, void (*del)(void *)*/)
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
			//del(lstnext);
			*lst = start;
			return ;
		}
		*lst = (*lst)->next;
	}
	*lst = start;
}
