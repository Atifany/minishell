#include "../_headers/minishell.h"

// char *get_env(t_list **env, char* key)
// {
// 	char	*value;
//
// 	value = getenv(key);	
// 	dict_set(env, key, value);	
// }


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
			if (strings[i][namelen] == '?')
				namelen++;
			else
				while (strings[i][namelen] && (ft_isalnum(strings[i][namelen])))
					namelen++;
			name = ft_substr(strings[i], 0, namelen);
			t = ft_strdup(dict_get(env, name));// check for t == NULL
			t = gnl_join(&t, strings[i]+namelen, ft_strlen(strings[i] + namelen));
			free(name);
			free(strings[i]);
			strings[i] = t;
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
		ft_strlcat(result, strings[i], total_len+1);	
		i++;
	}
	free(*arg);
	*arg = result;
	
}

void variable_handler(char **args, t_list **env)
{
	char **splitted;
	int i;
	
	i = 0;
	while (args[i])
	{
		if (args[i] && count(args[i], -50))
		{
			splitted = ft_split(args[i], -50);
			replace_envs(splitted, env, args[i][0] == -50);		
			replace_arg(splitted, args+i);
			free_array(splitted);
		}
		i++;
	}
}
