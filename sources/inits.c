# include "../minishell.h"

void	clear_struct(t_line *line)
{
	if (line->command)
		free(line->command);
	if (line->args)
		free_array(line->args);
	if (line->fd_to_write)
		free_array(line->fd_to_write);
	if (line->redir_input)
		free_struct_array(line->redir_input);
}

void	init_struct(t_line *line)
{
	line->pip_in = NULL;
	line->pip_out = NULL;
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	line->command = NULL;
	line->args = NULL;
	line->redir_input = NULL;
	line->fd_to_write = NULL;
	line->fd_to_appwrite = NULL;
	line->is_appending = FALSE;
	line->env = NULL;
	line->shell = NULL;
}

void	func_dict_init(t_list **func_dict)
{
	*func_dict = NULL;

	func *pwd;
	pwd = malloc(sizeof(func));
	pwd->foo = execute_pwd;
	dict_set(func_dict, "pwd", pwd);

	func *cd;
	cd = malloc(sizeof(func));
	cd->foo = execute_cd;
	dict_set(func_dict, "cd", cd);

	func *echo;
	echo = malloc(sizeof(func));
	echo->foo = execute_echo;
	dict_set(func_dict, "echo", echo);

	func *env;
	env = malloc(sizeof(func));
	env->foo = execute_env;
	dict_set(func_dict, "env", env);

	func *export;
	export = malloc(sizeof(func));
	export->foo = execute_export;
	dict_set(func_dict, "export", export);
}
