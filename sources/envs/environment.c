#include "../_headers/minishell.h"

char *get_env(t_list **env, char* key)
{
	char	*value;

	value = getenv(key);	
	dict_set(env, key, value);	
}


static void replace_envs(char **strings, t_list **env, int starts_with_dollar)
{
	char *t; 
	int i;
	int namelen;
	char* name;

	namelen = 0;
	i = -1;
	while (strings[++i])
	{
		namelen = 0;
		if (starts_with_dollar || i) 
		{
			while (strings[i][namelen] && strings[i][namelen] != ' ')
				namelen++;
			name = ft_substr(strings[i], 0, namelen);
			printf("point\n");
			t = ft_strdup(dict_get(env, name));// check for t == NULL
			printf("point\n")	;
			t = gnl_join(&t, strings[i]+namelen, ft_strlen(strings[i] + namelen));
			printf("point\n");
			free(strings[i]);
			strings[i] = t;
			free(name);
		}
	}
}


static void replace_arg(char** strings, char **arg)
{
	int n_of_strings;
	int total_len;
	int i;
	char *result;

	total_len = 0;
	i = -1;
	while (strings[++i])
		total_len += ft_strlen(strings[i]);
	result = ft_calloc(total_len+1, 1);
	n_of_strings = i;
	i = 0;
	while (n_of_strings > i)
	{
		ft_strlcat(result, ft_strdup(strings[i]), total_len+1);	
		i++;
	}
	free(*arg);
	*arg = result;
	
}

void variable_handler(char **args, t_list **env)
{
	int var_len;
	char **splitted;
	int i;
	int j;
	
	i = 0;
	var_len = 0;
	while (args[i])
	{
		if (args[i] && count(args[i], -50))
		{	
			j = -1;
			splitted = ft_split(args[i], -50);
			replace_envs(splitted, env, args[i][0] == -50);		
			replace_arg(splitted, args+i);
			free_array(splitted);
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