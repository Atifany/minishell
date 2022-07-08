/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:24:22 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:24:23 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static int	is_pipe(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	return ((0));
}

static int	is_redir(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	return (0);
}

// 1 -> not valid. 0 -> valid
int	validate(char **exec_line)
{
	int	i;

	i = 0;
	while (exec_line[i])
	{
		if (is_redir(exec_line[i]) && (is_redir(exec_line[i + 1])
				|| !exec_line[i + 1] || is_pipe(exec_line[i + 1])))
			return (1);
		else if (is_pipe(exec_line[i]) && (is_pipe(exec_line[i + 1])
				|| !exec_line[i + 1] || i == 0))
			return (1);
		i++;
	}
	return (0);
}
