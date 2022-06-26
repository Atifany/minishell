#include "../_headers/minishell.h"

void *dict_get(t_list **lst, char* key)
{
	t_list *start;

	start = *lst;
	while (start != NULL)
	{
		if (!ft_strcmp(((t_kv *)(start)->content)->key, key))
			return ((t_kv *)(start)->content)->value;
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
// 		printf("%p\n", ((func *)(((t_kv *)(*lst)->content)->value))->foo);
// 		*lst = (*lst)->next;
// 	}
// 	*lst = start;
// 	return NULL;
// }

void dict_add(t_list **lst, char* key, void* value)
{
	t_kv *t_kv;

	t_kv = malloc(16);
	t_kv->key = key;
	t_kv->value = value;
	ft_lstadd_back(lst, ft_lstnew(t_kv));
}

void dict_set(t_list **lst, char* key, void* value)
{
	t_list *start;

	start = *lst;
	while (*lst)
	{
		if (!ft_strcmp(((t_kv *)(*lst)->content)->key, key))
		{
			free(((t_kv *)(*lst)->content)->value);
			free(((t_kv *)(*lst)->content)->key);
			((t_kv *)(*lst)->content)->value = value;
			((t_kv *)(*lst)->content)->key = key;
			*lst = start;
			return ;
		}
		*lst = (*lst)->next;
	}
	*lst = start;
	dict_add(lst, key, value);
}

void dict_del(t_list **lst)
{
	t_list *next;

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
