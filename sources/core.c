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

int main()
{
	char	input_str[100000];
	//char	*commands[100000]

	ft_bzero(input_str, 100000);
	while (TRUE)
	{
		//print_dir();
		take_input(input_str);
		//printf("Confirm input: %s\n", input_str);
		//>>>>ANIME<<<<
		//>>>>>MUST<<<<
		//>>>>>>>DIE<<<
		//>>OMEGALOL<<<
		//exec_comms(commands);
	}
	return (0);
}