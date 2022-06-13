#include "../_headers/minishell.h"

char *get_env(t_list **env, char* key)
{
	char	*value;

	value = getenv(key);	
	dict_set(env, key, value);	
}

void variable_handler(char **args, t_list **env)
{
	char *t;
	int i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			t = dict_get(env, args[i]+1);
			free(args[i]);
			args[i] = ft_strdup(t);
		}
		i++;
	}
}

void add_vars(char **vars, t_list **env)
{
	char **t;
	while (*vars)
	{
		t = ft_split(*vars, '=');
		dict_set(env, t[0], t[1]);
		free_array(t);
		*vars++;
	}
}