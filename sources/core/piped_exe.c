/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:22:37 by atifany           #+#    #+#             */
/*   Updated: 2022/07/08 13:52:00 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../_headers/minishell.h"

static char	setup_pipes(t_line *line, char is_first_cmd)
{
	int	sig;

	if (is_first_cmd && *(line->redir_input))
		open_pip(&(line->pip_in));
	if (!is_first_cmd || *(line->redir_input))
	{
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
	if (line->is_piping || *(line->redir_output))
	{
		open_pip(&(line->pip_out));
		redirect(STDOUT_FILENO, line->pip_out[WRITE]);
	}
	open_pip(&(line->pip_talk));
	redirect(STDERR_FILENO, line->pip_talk[WRITE]);
	open_pip(&(line->pip_status));
	return (0);
}

static void	release_pipes(t_line *line, char is_first_cmd)
{
	if (line->is_piping || *(line->redir_output))
	{
		redirect(STDOUT_FILENO, line->save_stdout);
		close(line->pip_out[WRITE]);
	}
	if (!is_first_cmd || *(line->redir_input))
	{
		redirect(STDIN_FILENO, line->save_stdin);
		close(line->pip_in[READ]);
	}
	if (line->is_piping)
		open_pip(&(line->pip_in));
}

static char	forking_exe(t_line *line, char is_first_cmd)
{
	int	status;

	if (fork())
	{
		wait(&status);
		status = read_pip_status(line, status);
		set_last_ret_env(line, status);
		read_error_text(line);
		if (WIFSIGNALED(status) || status == 1)
		{
			release_pipes(line, is_first_cmd);
			return (1);
		}
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		exit(exe(line));
	}
	return (0);
}

static char	piped_exe_body(t_line *line, char is_first_cmd)
{
	int	status;

	status = setup_pipes(line, is_first_cmd);
	if (status)
	{
		set_last_ret_env(line, status);
		return (1);
	}
	if (forking_exe(line, is_first_cmd))
		return (1);
	release_pipes(line, is_first_cmd);
	write_output(line, line->is_piping);
	return (0);
}

char	piped_exe(t_line *line, char **exec_line)
{
	int					shift;
	int					total_shift;
	char				is_first_cmd;

	is_first_cmd = TRUE;
	signal(SIGINT, SIG_IGN);
	total_shift = 0;
	while (*exec_line)
	{
		line->error_text = NULL;
		shift = parse_line_to_struct(line, exec_line);
		total_shift += shift;
		exec_line += shift;
		if (piped_exe_body(line, is_first_cmd))
			break ;
		is_first_cmd = FALSE;
	}
	exec_line -= total_shift;
	free_array(exec_line);
	return (0);
}
