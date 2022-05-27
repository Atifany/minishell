#include "../minishell.h"

char *get_env(t_list **env, char* key)
{
	char	*value;

	value = dict_get(env, key); 
	if (value == NULL)
	{
		value = getenv(key);
		dict_set(env, key, value);
	}
	return value;
}