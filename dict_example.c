# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include "minishell.h"

typedef struct s_func
{
	char (*foo)(void *);
} t_func;

char hello_name(void *a)
{
	printf("hello %s\n", (char *)a);
	return 0;
}

char run(char (f)(void *), char *a)
{
	return f(a);
}

int main()
{
	t_list *functions = NULL;

	t_func *hw_func_struct;
	hw_func_struct = malloc(sizeof(t_func *));
	hw_func_struct->foo = hello_name;

	dict_set(&functions, "hw_func", hw_func_struct);
	
	((t_func *)dict_get(&functions, "hw_func"))->foo("Vasya");
	return (0);
}