/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/04/23 15:34:15 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	take_input(char *input_str)
{
	char	*buf;

	buf = readline("minishell>> ");
	ft_strlcpy(input_str, buf, 100000);
	return (TRUE);
}

static char **parse_to_array(char *input_str)
{
	char **array = ft_split(input_str);
	return (array);
}

int main()
{
	char	input_str[100000];
	//char	**exec_line;

	ft_bzero(input_str, 100000);
	while (TRUE)
	{
		//print_dir();
		take_input(input_str);
		//printf("Confirm input: %s\n", input_str);
		//exec_line = parse_to_array(input_str) //parse to comms and args array
		//choose_operation(exec_line) //choose command to execute
		execute_file(input_str);
	}
	return (0);
}