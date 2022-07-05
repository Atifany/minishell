/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dict_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:24:02 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:24:03 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

static void	init_first_half(t_line *line)
{
	t_func	*pwd;
	t_func	*cd;
	t_func	*echo;
	t_func	*env;

	pwd = malloc(sizeof(t_func));
	cd = malloc(sizeof(t_func));
	echo = malloc(sizeof(t_func));
	env = malloc(sizeof(t_func));
	pwd->foo = execute_pwd;
	cd->foo = execute_cd;
	echo->foo = execute_echo;
	env->foo = execute_env;
	dict_add(&(line->func_dict), ft_strdup("pwd"), pwd);
	dict_add(&(line->func_dict), ft_strdup("cd"), cd);
	dict_add(&(line->func_dict), ft_strdup("echo"), echo);
	dict_add(&(line->func_dict), ft_strdup("env"), env);
}

static void	init_second_half(t_line *line)
{
	t_func	*export;
	t_func	*unset;

	export = malloc(sizeof(t_func));
	unset = malloc(sizeof(t_func));
	export->foo = execute_export;
	unset->foo = execute_unset;
	dict_add(&(line->func_dict), ft_strdup("export"), export);
	dict_add(&(line->func_dict), ft_strdup("unset"), unset);
}

void	func_dict_init(t_line *line)
{	
	line->func_dict = NULL;
	init_first_half(line);
	init_second_half(line);
}
