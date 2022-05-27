#include "minishell.h"

char *get_value(t_list *env, char* key)
{
	while (env)
	{
		if (((kv *)env->content)->key == key)
			return ((kv *)env->content)->value;
		env = env->next;
	}
	return NULL;
}

void set_value(t_list **env, char* key, char* value)
{
	while (env)
	{
		if (((kv *)(*env)->content)->key == key)
		{
			((kv *)(*env)->content)->value = value;
			return ;
		}
		*env = (*env)->next;
		add_value(env, key, value);	
	}
}

void add_value(t_list **env, char* key, char* value)
{
	kv *kv;

	kv = malloc(16);
	kv->key = key;
	kv->value = value;
	ft_lstadd_back(env, ft_lstnew(kv));
}

char print_env(t_list *env)
{
	while (env)
	{
		printf("%s=%s", ((kv *)env->content)->key, ((kv *)env->content)->value);
		env = env->next;
	}
}