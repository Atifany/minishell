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
	char	**t;
	int		i;

	if ((line->args[1] && line->args[2])
		|| line->args[1] == NULL || count(line->args[2], '=') != 1)
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
	t = ft_split(line->args[1], '=');
	if (t[0] == NULL || t[1] == NULL)
		return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
	i = 0;
	while (t[1][i])
		if (!ft_isalnum(t[1][i++]))
			return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
	i = 0;
	while (t[0][i])
		if (!ft_isalnum(t[0][i++]))
			return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("-5")));
	dict_set(&(line->env), ft_strdup(t[0]), ft_strdup(t[1]));
	free_array(t);
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
		dict_delone(&(line->env), line->args[i]);
		i++;
	}
	return (dict_set(&(line->env), ft_strdup("?"), ft_strdup("0")));
}
