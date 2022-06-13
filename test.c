#include "sources/_headers/minishell.h"

static void	init_charpp(int size, void *arr){
	char ***arr_cpy = arr;
	if (*arr_cpy){
		free(*arr_cpy);
	}
	*arr_cpy = (char **)ft_calloc(sizeof(char *), (size + 1));
}

static void	init_structp(int size, void *arr){
	t_inqu	***arr_cpy = arr;
	if (*arr_cpy){
		free(*arr_cpy);
	}
	*arr_cpy = (t_inqu **)ft_calloc(sizeof(t_inqu), (size + 1));
}

static void	add_to_charpp(void *arr, char *str, char mode){
	int i = 0;
	(void)mode;

	while ((*(char ***)arr)[i]){
		i++;
	}
	(*(char ***)arr)[i] = ft_strdup(str);
}

static void	add_to_structp(void *arr, char *str, char mode){
	int i = 0;

	while ((*(t_inqu ***)arr)[i]){
		i++;
	}
	(*(t_inqu ***)arr)[i] = (t_inqu *)malloc(sizeof(t_inqu *));
	(*(t_inqu ***)arr)[i]->arg = ft_strdup(str);
	(*(t_inqu ***)arr)[i]->mode = mode;
}

static char	is_arrow(char *str){
	if (!ft_strcmp(str, ">") ||
		!ft_strcmp(str, ">>") ||
		!ft_strcmp(str, "<") ||
		!ft_strcmp(str, "<<"))
	{
		return (TRUE);
	}
	return (FALSE);
}

static char	identify(char **exec_line, int i){
	// first elem rule
	if (i == 0){
		if (!is_arrow(exec_line[i])){
			return (ARG);
		}
		return (ARROW);
	}
	// argument rule
	if (!is_arrow(exec_line[i]) && !is_arrow(exec_line[i - 1])){
		return (ARG);
	}
	// redirects rule
	if (!is_arrow(exec_line[i]) && is_arrow(exec_line[i - 1])){
		if (!ft_strcmp(exec_line[i - 1], ">")){
			return (FD_WRITE);
		}
		if (!ft_strcmp(exec_line[i - 1], ">>")){
			return (FD_AP_WRITE);
		}
		if (!ft_strcmp(exec_line[i - 1], "<")){
			return (FD_READ);
		}
		if (!ft_strcmp(exec_line[i - 1], "<<")){
			return (FD_READ);
		}
	}
	return (ERROR);
}

static int	iterate_line(char **exec_line, void *arr, char to_search, char mode,
	void (*add)(void *, char *, char)){
	char	ret_identify;
	int	ret = 0;
	int i = 0;
	int j = 0;

	while (exec_line[i]){
		if (!ft_strcmp(exec_line[i], "|")){
			break ;
		}
		ret_identify = identify(exec_line, i);
		if (ret_identify == to_search){
			if (mode == COUNT){
				ret++;
			}
			if (mode == COLLECT){
				add(arr, exec_line[i], ft_strcmp(exec_line[ft_to_positive(i - 1)], "<"));
			}
		}
		i++;
	}
	return (ret);
}

static int	parse(char **exec_line, void *arr, t_methods meths, char to_search){
	int	ret;

	ret = iterate_line(exec_line, arr, to_search, COUNT, meths.add);
	((void (*)(int, void *))meths.init)(ret, arr);
	iterate_line(exec_line, arr, to_search, COLLECT, meths.add);
	return (ret);
}

int main(int argc, char **argv)
{
	int i = 0;
	char	**char_arr;
	t_inqu	**struct_arr;

	parse(argv, &char_arr, (t_methods){&init_charpp, &add_to_charpp}, ARG);
	parse(argv, &struct_arr, (t_methods){&init_structp, &add_to_structp}, FD_READ);

	// prints
	printf("char arr:");
	i = 0;
	while (char_arr[i]){
		printf(" |%s|", char_arr[i]);
		i++;
	}
	printf("\n");
	free_array(char_arr);
	printf("struct arr:");
	i = 0;
	while (struct_arr[i]){
		printf(" |%s:", struct_arr[i]->arg);
		printf("%d|", struct_arr[i]->mode);
		i++;
	}
	printf("\n");
}