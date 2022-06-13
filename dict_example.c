# include <stdio.h>
# include <unistd.h>
# include "sources/_headers/minishell.h"
# include "libs/libft/libft.h"

typedef struct s_func1
{
	char (*foo)(void *);
} t_func1;

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

	t_func1 *hw_func_struct;
	hw_func_struct = malloc(sizeof(t_func1 *));
	hw_func_struct->foo = hello_name;

	dict_set(&functions, "hw_func", hw_func_struct);
	
	t_func1 *getwtf =((t_func1 *)dict_get(&functions, "hw_func"));
	getwtf->foo("Vasya");
	//((t_func1 *)dict_get(&functions, "hw_func"))->foo("Vasya");
	return (0);
}