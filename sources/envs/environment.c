/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:39:57 by alex              #+#    #+#             */
/*   Updated: 2022/06/26 19:09:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

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
			if (strs[i][namelen] == '?')
				namelen++;
			else
				while (strs[i][namelen] && (ft_isalnum(strs[i][namelen])))
					namelen++;
			name = ft_substr(strs[i], 0, namelen);
			t = ft_strdup(dict_get(env, name));
			t = gnl_join(&t, strs[i] + namelen, ft_strlen(strs[i] + namelen));
			free(name);
			free(strs[i]);
			strs[i] = t;
		}
	}
}

static void	replace_arg(char **strings, char **arr)
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
	free(*arr);
	*arr = result;
}

void	variable_handler(char **arr, t_list **env)
{
	char	**splitted;
	if (*arr && count(*arr, -50))
	{
		splitted = ft_split(*arr, -50);
		replace_envs(splitted, env, (*arr)[0] == -50);
		replace_arg(splitted, arr);
		free_array(splitted);
	}
}
