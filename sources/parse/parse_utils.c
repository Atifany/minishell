/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:14:16 by atifany           #+#    #+#             */
/*   Updated: 2022/06/26 19:12:55 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

void	refresh_pip_out(t_line *line)
{
	if (line->pip_out)
	{
		free(line->pip_out);
		line->pip_out = NULL;
	}
	line->pip_out = malloc(sizeof(int) * 2);
	pipe(line->pip_out);
}

static char	is_arrow(char *str)
{
	if (!ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<")
		|| !ft_strcmp(str, "<<"))
	{
		return (TRUE);
	}
	return (FALSE);
}

// first elem is checked separately,
// than args are found and finally the redirects are found
char	identify(char **exec_line, int i)
{
	if (i == 0)
	{
		if (!is_arrow(exec_line[i]))
			return (ARG);
		return (ARROW);
	}
	if (!is_arrow(exec_line[i]) && !is_arrow(exec_line[i - 1]))
		return (ARG);
	if (!is_arrow(exec_line[i]) && is_arrow(exec_line[i - 1]))
	{
		if (!ft_strcmp(exec_line[i - 1], ">")
			|| !ft_strcmp(exec_line[i - 1], ">>"))
			return (FD_WRITE);
		if (!ft_strcmp(exec_line[i - 1], "<")
			|| !ft_strcmp(exec_line[i - 1], "<<"))
			return (FD_READ);
	}
	return (ERROR);
}

char	identify_arrow(char *arrow)
{
	if (!ft_strcmp(arrow, ">"))
		return (FD_WRITE);
	if (!ft_strcmp(arrow, ">>"))
		return (FD_APWRITE);
	if (!ft_strcmp(arrow, "<"))
		return (FD_READ);
	else
		return (FD_APREAD);
}
