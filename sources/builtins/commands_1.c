#include "../_headers/minishell.h"

char	execute_pwd(t_line *line)
{
	char	*buf;

	(void)line;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		write(2, "Error: cannot get current working directory\n", 45);
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

char	execute_env(t_line *line)
{
	t_list	*env;

	if (line->args[1])
	{
		write(2, "env: too many arguments\n", 25);
		return (1);
	}
	env = line->env;
	while (env)
	{
		if (ft_strcmp((char *)((t_kv *)env->content)->key, "?"))
			printf("%s=%s\n", (char *)((t_kv *)env->content)->key,
				(char *)((t_kv *)env->content)->value);
		env = env->next;
	}
	return (0);
}

static char	exit_export(char *name)
{
	if (name)
		free(name);
	write(2, "export: incorrect argument\n", 28);
	return (1);
}

// dobavit oshibku soderjit v imeni zapreshennie v rf simvoli
char	execute_export(t_line *line)
{
	char	*name;
	char	*value;
	int		i;

	name = NULL;
	i = 0;
	if ((line->args[1] && line->args[2])
		|| line->args[1] == NULL || !count(line->args[1], '='))
		return (exit_export(name));
	value = ft_strchr(line->args[1], '=') + 1;
	name = ft_substr(line->args[1], 0,
			ft_strlen(line->args[1]) - ft_strlen(value) - 1);
	if (value == NULL || name == NULL)
		return (exit_export(name));
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i++]))
			return (exit_export(name));
	}
	dict_set(&(line->env), name, ft_strdup(value));
	return (0);
}

char	execute_unset(t_line *line)
{
	int	i;

	if (!(line->args[1]))
	{
		write(2, "unset: no envs specified\n", 27);
		return (1);
	}
	i = 1;
	while (line->args[i])
	{
		if (dict_get(&(line->env), line->args[i]))
			dict_delone(&(line->env), line->args[i]);
		i++;
	}
	return (0);
}
