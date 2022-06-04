#include "../minishell.h"

// for char **
void	init_charpp(int size, void *arr){
	char ***arr_cpy = arr;
	if (*arr_cpy){
		free(*arr_cpy);
	}
	*arr_cpy = (char **)ft_calloc(sizeof(char *), (size + 1));
}

void	add_to_charpp(void *arr, char *str, char mode){
	int i = 0;
	(void)mode;

	while ((*(char ***)arr)[i]){
		i++;
	}
	(*(char ***)arr)[i] = ft_strdup(str);
}

// for t_inqu **
void	init_structpp(int size, void *arr){
	t_inqu	***arr_cpy = arr;
	if (*arr_cpy){
		free(*arr_cpy);
	}
	*arr_cpy = (t_inqu **)ft_calloc(sizeof(t_inqu), (size + 1));
}

void	add_to_structpp(void *arr, char *str, char mode){
	int i = 0;

	while ((*(t_inqu ***)arr)[i]){
		i++;
	}
	(*(t_inqu ***)arr)[i] = (t_inqu *)malloc(sizeof(t_inqu *));
	(*(t_inqu ***)arr)[i]->arg = ft_strdup(str);
	(*(t_inqu ***)arr)[i]->mode = mode;
}
