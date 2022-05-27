# include <stdio.h>
# include <unistd.h>
# include "sources/enviroment.c"
# include "sources/dictionary.c"
# include "sources/commands.c"
# include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	t_list *env;

	get_env(&env, "HOME");
	dict_set(&env, "aboba", "FAT");
	dict_set(&env, "boba", "gay");
	dict_del(&env, "aboba");
	execute_env(env);
	return (0);
}