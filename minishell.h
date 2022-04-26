/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:47:55 by atifany           #+#    #+#             */
/*   Updated: 2022/04/23 15:47:56 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include "libs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

// macros
# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define INT_MIN -2147483648

//colors
# define BLK "\e[0;30m"
# define BBLK "\e[1;30m"
# define RED "\e[0;31m"
# define BRED "\e[1;31m"
# define GRN "\e[0;32m"
# define BGRN "\e[1;32m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"
# define BLU "\e[0;34m"
# define BBLU "\e[1;34m"
# define MAG "\e[0;35m"
# define BMAG "\e[1;35m"
# define CYN "\e[0;36m"
# define BCYN "\e[1;36m"
# define WHT "\e[0;37m"
# define BWHT "\e[1;37m"
# define NC "\e[0m"

//utils
void	free_array(char **array);

// implemented built-in's
char	execute_file(char *command, char **arguments);
char	print_dir(void);

#endif