/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:33 by atifany           #+#    #+#             */
/*   Updated: 2022/07/08 13:11:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static void	cd_spec_symbol_handler(t_line *line, char **path,
	char *prev_path)
{
	char	*buf1;
	char	*buf2;

	if (!line->args[1])
		*path = ft_strdup((char *)dict_get(&(line->env), "HOME"));
	else
	{
		if (*(line->args[1]) == '~')
		{
			buf1 = ft_strdup((char *)dict_get(&(line->env), "HOME"));
			buf2 = ft_strdup(line->args[1] + 1);
			*path = gnl_join(&buf1, buf2,
					ft_strlen(line->args[1] + 1));
			free(buf2);
		}
		else if (!ft_strcmp(line->args[1], "-"))
			*path = ft_strdup(prev_path);
		else
			*path = ft_strdup(line->args[1]);
	}
}

char	execute_cd(t_line *line)
{
	int			dir;
	char		*path;

	if (line->args[1] && line->args[2])
	{
		write(2, "cd: too many args\n", 19);
		return (1);
	}
	if (!dict_get(&(line->env), "OLDPWD"))
		dict_set(&(line->env), ft_strdup("OLDPWD"), getcwd(NULL, 0));
	cd_spec_symbol_handler(line, &path, dict_get(&(line->env), "OLDPWD"));
	dict_set(&(line->env), ft_strdup("OLDPWD"), getcwd(NULL, 0));
	dir = chdir(path);
	if (!ft_strcmp(line->args[1], "-"))
		printf("%s\n", path);
	free(path);
	if (dir == -1)
	{
		write(2, "cd: specified path not found\n", 30);
		return (1);
	}
	return (0);
}

char	execute_echo(t_line *line)
{
	char	nl_flag;
	char	**args;

	args = line->args + 1;
	nl_flag = '\n';
	if (!*args)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strcmp(args[0], "-n"))
	{
		args++;
		nl_flag = '\0';
	}
	while (*(args) && *(args + 1))
	{
		write(1, *args, ft_strlen(*args));
		write(1, " ", 1);
		args++;
	}
	write(1, *args, ft_strlen(*args));
	write(1, &nl_flag, 1);
	return (0);
}

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

char	execute_exit(t_line *line)
{
	if (line->args[1] && line->args[2])
	{
		write(2, "cd: too many args\n", 19);
		return (1);
	}
	line->is_exit_pressed = TRUE;
	if (line->args[1])
		line->shell_exit_status = ft_atoi(line->args[1]);
	return 0;
}