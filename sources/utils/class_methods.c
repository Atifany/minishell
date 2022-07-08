/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:23:54 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:23:55 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

// for char **
void	init_charpp(int size, void *arr)
{
	char	***arr_cpy;

	arr_cpy = arr;
	if (*arr_cpy)
		free_array(*arr_cpy);
	*arr_cpy = (char **)ft_calloc(size + 1, sizeof(char *));
}

void	add_to_charpp(void *arr, char *str, char mode)
{
	int	i;

	(void)mode;
	i = 0;
	while ((*(char ***)arr)[i])
		i++;
	(*(char ***)arr)[i] = ft_strdup(str);
}

// for t_inqu **
void	init_structpp(int size, void *arr)
{
	t_inqu	***arr_cpy;

	arr_cpy = arr;
	if (*arr_cpy)
		free_struct_array(*arr_cpy);
	*arr_cpy = (t_inqu **)ft_calloc(size + 1, sizeof(t_inqu));
}

void	add_to_structpp(void *arr, char *str, char mode)
{
	int	i;

	i = 0;
	while ((*(t_inqu ***)arr)[i])
		i++;
	(*(t_inqu ***)arr)[i] = (t_inqu *)malloc(sizeof(t_inqu));
	(*(t_inqu ***)arr)[i]->arg = ft_strdup(str);
	(*(t_inqu ***)arr)[i]->mode = mode;
}
