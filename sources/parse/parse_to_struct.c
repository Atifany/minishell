#include "../_headers/minishell.h"

// // tmp func. Delete it later.
// void	temp_print_struct(t_line *line){
// 	int i;

// 	printf("command: %s\n", line->command);
// 	printf("args: ");
// 	i = 0;
// 	while (line->args[i]){
// 		printf("%s ", line->args[i++]);
// 	}
// 	printf("\n");
// 	printf("writes: ");
// 	i = 0;
// 	while (line->redir_output[i]){
// 		printf(" |%s:", line->redir_output[i]->arg);
// 		printf("%d|", line->redir_output[i]->mode);
// 		i++;
// 	}
// 	printf("\n");
// 	printf("reads:");
// 	i = 0;
// 	while (line->redir_input[i]){
// 		printf(" |%s:", line->redir_input[i]->arg);
// 		printf("%d|", line->redir_input[i]->mode);
// 		i++;
// 	}
// 	printf("\n");
// }

static int	iterate_line(char **exec_line, void *arr, t_transfer mods,
	void (*add)(void *, char *, char)){
	char	ret_identify;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (exec_line[i])
	{
		if (!ft_strcmp(exec_line[i], "|"))
			break ;
		ret_identify = identify(exec_line, i);
		if (ret_identify == mods.to_search)
		{
			if (mods.mode == COUNT)
				ret++;
			if (mods.mode == COLLECT)
				add(arr, exec_line[i],
					identify_arrow(exec_line[ft_to_positive(i - 1)]));
		}
		i++;
	}
	return (ret);
}

static int	parse(char **exec_line, void *arr,
	t_methods meths, char to_search)
{
	int	ret;

	ret = iterate_line(exec_line, arr,
			(t_transfer){to_search, COUNT}, meths.add);
	meths.init(ret, arr);
	iterate_line(exec_line, arr,
		(t_transfer){to_search, COLLECT}, meths.add);
	return (ret);
}

static int	check_parse_error(char **exec_line)
{
	int		i;

	i = 0;
	while (exec_line[i])
	{
		if (!ft_strcmp(exec_line[i], "|"))
			break ;
		if (is_arrow(exec_line[i])
			&& (is_arrow(exec_line[i + 1])
				|| !ft_strcmp(exec_line[i + 1], "|")
				|| !exec_line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

// multyplied total_shift by two because "> keks.txt" (arrow present)
static int	fill_struct(t_line *line, char **exec_line)
{
	int	total_shift;

	if (check_parse_error(exec_line))
		return (-1);
	total_shift = parse(exec_line, &(line->args),
			(t_methods){&init_charpp, &add_to_charpp}, ARG);
	variable_handler((line->args), &(line->env));
	if (line->command)
		free(line->command);
	line->command = ft_strdup(line->args[0]);
	total_shift += 2 * parse(exec_line, &(line->redir_output),
			(t_methods){&init_structpp, &add_to_structpp}, FD_WRITE);
	total_shift += 2 * parse(exec_line, &(line->redir_input),
			(t_methods){&init_structpp, &add_to_structpp}, FD_READ);
	return (total_shift);
}

// Second if clause means find_* funcs stoped at pipe, not a EOL
// use to debug: temp_print_struct(line);
int	parse_line_to_struct(t_line *line, char **exec_line)
{
	int	total_shift;

	refresh_pip_out(line);
	total_shift = fill_struct(line, exec_line);
	if (total_shift < 0)
		return (total_shift);
	quote_handler(line->args);
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	if (*(exec_line + total_shift) != NULL)
	{
		line->is_piping = TRUE;
		line->is_redirecting = TRUE;
		total_shift++;
	}
	if (*(line->redir_output))
		line->is_redirecting = TRUE;
	return (total_shift);
}
