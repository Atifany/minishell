/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:46 by atifany           #+#    #+#             */
/*   Updated: 2022/07/05 12:22:47 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../_headers/minishell.h"

static char	setup_pipes(t_line *line)
{
	int	sig;

	if (*(line->redir_input))
	{
		open_pip(&(line->pip_in));
		sig = cat_to_pipe_in(line);
		if (sig)
		{
			close(line->pip_in[WRITE]);
			close(line->pip_in[READ]);
			return (sig);
		}
		redirect(STDIN_FILENO, line->pip_in[READ]);
		close(line->pip_in[WRITE]);
	}
	if (*(line->redir_output))
	{
		open_pip(&(line->pip_out));
		redirect(STDOUT_FILENO, line->pip_out[WRITE]);
	}
	open_pip(&(line->pip_talk));
	redirect(STDERR_FILENO, line->pip_talk[WRITE]);
	open_pip(&(line->pip_status));
	return (0);
}

static void	release_pipes(t_line *line)
{
	if (*(line->redir_output))
	{
		redirect(STDOUT_FILENO, line->save_stdout);
		close(line->pip_out[WRITE]);
		write_output(line, FALSE);
	}
	if (*(line->redir_input))
	{
		redirect(STDIN_FILENO, line->save_stdin);
		close(line->pip_in[READ]);
	}
}

char	simple_exe(t_line *line, char **exec_line)
{
	int		ret;

	parse_line_to_struct(line, exec_line);
	free_array(exec_line);
	ret = setup_pipes(line);
	if (ret)
	{
		set_last_ret_env(line, ret);
		return (0);
	}
	ret = exe(line);
	ret <<= 8;
	redirect(STDERR_FILENO, line->save_stderr);
	ret = read_pip_status(line, ret);
	set_last_ret_env(line, ret);
	read_error_text(line);
	release_pipes(line);
	return (0);
}
