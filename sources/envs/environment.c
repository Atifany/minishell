/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:39:57 by alex              #+#    #+#             */
/*   Updated: 2022/06/27 13:31:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static void decode(char **str)
{
	int  i;

	i = 0;
	while ((*str)[i])
	{
		(*str)[i] = -(*str)[i]; 
		i++;
	}
}

static void	replace_envs(char **strs, t_list **env, int starts_with_dollar)
{
	char	*t;
	int		i;
	int		namelen;
	char	*name;

	i = -1;
	while (strs[++i])
	{
		namelen = 0;
		if (starts_with_dollar || i)
		{
			while (strs[i][namelen] && (strs[i][namelen] < 0))
				namelen++;
			name = ft_substr(strs[i], 0, namelen);
			decode(&name);

			t = ft_strdup(dict_get(env, name));
			t = gnl_join(&t, strs[i] + namelen, ft_strlen(strs[i] + namelen));
			free(name);
			free(strs[i]);
			strs[i] = t;
		}
	}
}

static void	replace_arg(char **strings, char **arg)
{
	int		n_of_strings;
	int		total_len;
	int		i;
	char	*result;

	total_len = 0;
	i = -1;
	while (strings[++i])
		total_len += ft_strlen(strings[i]);
	result = ft_calloc(total_len + 1, 1);
	n_of_strings = i;
	i = 0;
	while (n_of_strings > i)
	{
		ft_strlcat(result, strings[i], total_len + 1);
		i++;
	}
	free(*arg);
	*arg = result;
}

void	variable_handler(char **args, t_list **env)
{
	char	**splitted;
	int		i;
		
	i = 0;
	while (args[i])
	{
		if (args[i] && count(args[i], -37))
		{
			splitted = ft_split(args[i], -37);
			replace_envs(splitted, env, args[i][0] == -37);
			replace_arg(splitted, args + i);
			free_array(splitted);
		}
		i++;
	}
}
