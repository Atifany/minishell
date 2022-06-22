/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:47:55 by atifany           #+#    #+#             */
/*   Updated: 2022/05/27 18:31:40 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include <errno.h>
# include "../../libs/libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "get_next_line.h"

// general macros
# define READ 0 	// never touch it
# define WRITE 1 	// never touch it
# define INIT 2
# define OPEN 3
# define CLOSE 4
# define APPEND 5
# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define STR_EMPTY ""
// parser macros
# define COUNT 0
# define COLLECT 1
// identifier macros
# define CMD 0
# define ARROW 1
# define ARG 2
# define FD_WRITE 3
# define FD_AP_WRITE 4
# define FD_READ 5
# define FD_AP_READ 6
# define ERROR 8
// read macros
# define READ_BUFFER_SIZE 1024 // 1KB

//global
# ifndef GLOBAL
#  define GLOBAL
int	child_pid;
# endif

typedef	struct s_transfer
{
	char	to_search;
	char	mode;
}	t_transfer;

typedef struct s_key_value
{
	char *key;
	void *value;
}	kv;

typedef struct s_basic_methods
{
	void (*init)(int, void *);
	void (*add)(void *, char *, char);
}	t_methods;

typedef struct s_input_queue
{
	char	*arg;
	char	mode;
}	t_inqu;

//line format
typedef struct s_line
{
	// better sort it with "union"
	char	*command;
	char	**args;
	char	**fd_to_write;
	char	**fd_to_appwrite;
	t_inqu	**redir_input;
	char	is_redirecting;	// turns on/off redirector for every cmd
	char	is_piping;		// tells writer to write all output to pipe_in also;
	int		*pip_in;		// pipe from which every command reads (stdin is redirected here)
	int		*pip_out;		// pipe to which every command writes (including pipe_in if needed)
	char	is_appending;
	t_list	*func_dict;
	t_list	*env;
	t_list	*cmds;
}	t_line;

char	process_input(t_line *line);
char	ft_switch(t_line *line);

// inits
void	init_struct(t_line *line);
void	clear_struct(t_line *line);
void	func_dict_init(t_list **func_dict);
void	init_env(t_list **env);

// pipe_in controller
void	cat_to_pipe_in(t_line *line);
char	open_pipe_in(t_line *line, char mode);

// Redirects file output to a chosen file
void	redirect_output(t_line *line, char mode);
void	redirect_input(t_line *line, char mode);

// Class methods
void	init_charpp(int size, void *arr);
void	add_to_charpp(void *arr, char *str, char mode);
void	init_structpp(int size, void *arr);
void	add_to_structpp(void *arr, char *str, char mode);

// parse utils
void	refresh_pip_out(t_line *line);
char	identify(char **exec_line, int i);
int		arr_len(void **array);

// utils
int		ft_to_positive(int n);
int		ft_cat(int fd, char **str_ptr);
int		ft_strcmp(char *str1, char *str2);
void	free_struct_array(t_inqu **array);
void	free_array(char **array);
int		print_error(int error);


// implemented built-in's
void	execute_file(t_line *line);
void	execute_pwd(t_line *line);
void	execute_cd(t_line *line);
void	execute_echo(t_line	*line);
void	execute_env(t_line *line);
void	execute_export(t_line *line);
void	execute_cat(t_line *line);

typedef struct s_func
{
	void (*foo)(t_line *);
}	func;


// parse to struct
int		parse_line_to_struct(t_line *line, char **exec_line);
char	**parse_to_array(char *input_str);

// parse utils
int	arrlen(char **arr);
int contains(char *arr);
char **dropnulls(char **arr, int len);
void dropquotes(char **arr);
char	*ft_strj(char *s1, char *s2);
int count(char *arr, char s);

//dict
void *dict_get(t_list **lst, char* key);
void dict_set(t_list **lst, char* key, void* value);
void dict_del(t_list **lst);
void dict_add(t_list **lst, char* key, void* value);

//env
char *get_env(t_list **env, char* key);
void variable_handler(char **args, t_list **env);

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

#endif
