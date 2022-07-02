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
# define DEINIT 6
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
# define FD_WRITE '>'
# define FD_APWRITE '>' + 1
# define FD_READ '<'
# define FD_APREAD '<' + 1
# define ERROR 8
// read macros
# define READ_BUFFER_SIZE 1024 // 1KB

//global
# ifndef GLOBAL
#  define GLOBAL

int	g_child_pid;
# endif

// utility struct for parser needs
typedef struct s_transfer
{
	char	to_search;
	char	mode;
}	t_transfer;

// dictionary stowage
typedef struct s_key_value
{
	char	*key;
	void	*value;
}	t_kv;

// utility struct for parser needs
typedef struct s_basic_methods
{
	void	(*init)(int, void *);
	void	(*add)(void *, char *, char);
}	t_methods;

// used to store input and output filenames
typedef struct s_input_queue
{
	char	*arg;
	char	mode;
}	t_inqu;

// Global struct
// is_redirecting turns on/off redirector for every cmd
// is_piping tells writer to write all output to pipe_in also;
// pip_in is a pipe
//  from which every command reads (stdin is redirected here)
// pip_out is a pipe
//  to which every command writes (including pipe_in if needed)
// is_newline is set to TRUE each readline.
typedef struct s_line
{
	int		save_stdin;
	int		save_stdout;
	int		save_stderr;
	char	*command;
	char	**args;
	t_inqu	**redir_output;
	t_inqu	**redir_input;
	char	is_redirecting;
	char	is_piping;
	char	is_newline;
	int		*pip_in;
	int		*pip_out;
	int		*pip_talk;
	int		*pip_status;
	char	*error_text;
	char	is_exit_pressed;
	t_list	*func_dict;
	t_list	*env;
	t_list	*cmds;
}	t_line;

char	process_input(t_line *line);
int		ft_switch(t_line *line);
char	simple_exe(t_line *line, char **exec_line);
char	piped_exe(t_line *line, char **exec_line);

// processing utils
int		exe(t_line *line);
void	read_error_text(t_line *line);
char	**take_input(void);
void	redirect(int from, int to);
void	open_pip(int **pip);
char	*rl_take_input(void);
void	set_last_ret_env(t_line *line, int status);
int		read_pip_status(t_line *line, int status);

// signals
void	signals_default();
void	signals_ignore();
void	sigint_hook(int sig);

// inits
void	init_struct(t_line *line);
void	clear_struct(t_line *line);
void	clear_pips(t_line *line);
void	func_dict_init(t_line *line);
void	init_env(t_line *line);
void	init_streams(t_line *line);

// pipe_in controller
char	cat_to_pipe_in(t_line *line);
char	open_pipe_in(t_line *line, char mode);

// Redirects file output to a chosen file
void	write_output(t_line *line, char is_piping);
void	redirect_output(t_line *line, char mode);
void	redirect_input(t_line *line, char mode);
void	open_files(t_line *line, int **fds);
void	close_files(int *fds);

// Class methods
void	init_charpp(int size, void *arr);
void	add_to_charpp(void *arr, char *str, char mode);
void	init_structpp(int size, void *arr);
void	add_to_structpp(void *arr, char *str, char mode);

// parse utils
void	refresh_pip_out(t_line *line);
char	identify(char **exec_line, int i);
char	identify_arrow(char *arrow);
int		arr_len(void **array);
void	quote_handler(char **args);
char	is_arrow(char *str);

// utils
int		ft_to_positive(int n);
int		ft_cat(int fd, char **str_ptr);
int		ft_strcmp(char *str1, char *str2);
void	free_struct_array(t_inqu **array);
void	free_array(char **array);
void	print_error(t_line *line);
char	is_in_array(char **array, char *str);
int		validate(char **exec_line);

// implemented built-in's
int		execute_file(t_line *line);
char	execute_pwd(t_line *line);
char	execute_cd(t_line *line);
char	execute_echo(t_line	*line);
char	execute_env(t_line *line);
char	execute_export(t_line *line);
char	execute_unset(t_line *line);

typedef struct s_func
{
	char	(*foo)(t_line *);
}	t_func;

// parse to struct
int		parse_line_to_struct(t_line *line, char **exec_line);
char	**parse_to_array(char *input_str);

// parse utils
int		arrlen(char **arr);
char	**dropnulls(char **arr, int len);
void	dropquotes(char **arr);
char	*ft_strj(char *s1, char *s2);
int		count(char *arr, char s);

//dict
void	*dict_get(t_list **lst, char *key);
void	dict_set(t_list **lst, char *key, void *value);
void	dict_del(t_list **lst);
void	dict_delone(t_list **lst, char *key);
void	dict_add(t_list **lst, char *key, void *value);

//env
//char	*get_env(t_list **env, char *key);
void	variable_handler(char **arr, t_list **env);

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
