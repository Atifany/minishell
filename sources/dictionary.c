#include "minishell.h"

char *get_value(t_list *lst, char* key)
{
	while (lst)
	{
		if (((kv *)lst->content)->key == key)
			return ((kv *)lst->content)->value;
		lst = lst->next;
	}
	return NULL;
}

void set_value(t_list **lst, char* key, void* value)
{
	while (lst)
	{
		if (((kv *)(*lst)->content)->key == key)
		{
			((kv *)(*lst)->content)->value = value;
			return ;
		}
		*lst = (*lst)->next;
		add_value(lst, key, value);	
	}
}

void add_value(t_list **lst, char* key, void* value)
{
	kv *kv;

	kv = malloc(16);
	kv->key = key;
	kv->value = value;
	ft_lstadd_back(lst, ft_lstnew(kv));
}

char print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s=%s", ((kv *)lst->content)->key, ((kv *)lst->content)->value);
		lst = lst->next;
	}
}