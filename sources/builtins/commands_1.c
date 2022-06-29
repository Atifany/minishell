#include "../_headers/minishell.h"

void	execute_pwd(t_line *line)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-2")));
	printf("%s\n", buf);
	free(buf);
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}

void	execute_env(t_line *line)
{
	t_list	*env;

	if (line->args[1])
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-6")));
	env = line->env;
	while (env)
	{
		if (ft_strcmp((char *)((t_kv *)env->content)->key, "?"))
			printf("%s=%s\n", (char *)((t_kv *)env->content)->key,
				(char *)((t_kv *)env->content)->value);
		env = env->next;
	}
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}

// dobavit oshibku soderjit v imeni zapreshennie v rf simvoli
void	execute_export(t_line *line)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	if ((line->args[1] && line->args[2])
		|| line->args[1] == NULL || !count(line->args[1], '='))
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
	value = ft_strchr(line->args[1], '=') + 1;
	name = ft_substr(line->args[1], 0, ft_strlen(line->args[1]) - ft_strlen(value) - 1);
	if (value == NULL || name == NULL)
	{
		free(name);
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
	}
	while (name[i])
	{
		printf("%s\n", name);
		if (name[i] != '_' && !ft_isalnum(name[i++]))
		{
			free(name);
			return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
		}
	}
	dict_set(&(line->env), name, ft_strdup(value));
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}

void	execute_cat(t_line *line)
{
	int		i;
	char	*str;
	int		fd;

	if (!(line->args[1]))
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-10")));
	i = 1;
	while (line->args[i])
	{
		fd = open(line->args[i], O_CREAT | O_RDWR, 0666);
		if (fd < 0)
			return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-9")));
		while (ft_cat(fd, &str) > 0)
		{
			write(1, str, ft_strlen(str));
			free(str);
			str = NULL;
		}
		close(fd);
		i++;
	}
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}

void	execute_unset(t_line *line)
{
	int	i;

	if (!(line->args[1]))
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-11")));
	i = 1;
	while (line->args[i])
	{
		if (dict_get(&(line->env), line->args[i]))
			dict_delone(&(line->env), line->args[i]);
		i++;
	}
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}
