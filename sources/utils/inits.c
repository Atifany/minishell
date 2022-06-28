<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:01:28 by atifany           #+#    #+#             */
/*   Updated: 2022/06/28 13:40:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
>>>>>>> 17f67157d6a51b1e984e2c7eddcaf4473b94660a
#include "../_headers/minishell.h"

void	clear_struct(t_line *line)
{
	if (line->command)
		free(line->command);
	if (line->args)
		free_array(line->args);
	if (line->redir_output)
		free_struct_array(line->redir_output);
	if (line->redir_input)
		free_struct_array(line->redir_input);
	if (line->pip_in)
		free(line->pip_in);
	if (line->pip_out)
		free(line->pip_out);
}

void	init_env(t_line *line)
{
	int	i;

	i = 0;
	line->env = NULL;
	char *names[] = {"SHELL", "SESSION_MANAGER", "QT_ACCESSIBILITY", "COLORTERM", "GNOME_DESKTOP_SESSION_ID", 
	"LANGUAGE", "LC_ADDRESS", "LC_NAME", "SSH_AUTH_SOCK", "CINNAMON_VERSION", "LC_MONETARY", 
	"SSH_AGENT_PID", "CINNAMON_SLOWDOWN_FACTOR", "GTK_MODULES", "PWD", "LOGNAME", "QT_QPA_PLATFORMTHEME", 
	"XDG_SESSION_TYPE", "GPG_AGENT_INFO", "PULSE_SCRIPT", "GJS_DEBUG_TOPICS", "HOME", "LC_PAPER", "LANG", 
	"LS_COLORS", "XDG_CURRENT_DESKTOP", "VTE_VERSION", "XRDP_SOCKET_PATH", "XRDP_PULSE_SOURCE_SOCKET", 
	"GNOME_TERMINAL_SCREEN", "GJS_DEBUG_OUTPUT", "LESSCLOSE", "XDG_SESSION_CLASS", "TERM", 
	"LC_IDENTIFICATION", "GTK_OVERLAY_SCROLLING", "LESSOPEN", "USER", "CINNAMON_SOFTWARE_RENDERING", 
	"GNOME_TERMINAL_SERVICE", "XRDP_SESSION", "DISPLAY", "XRDP_PULSE_SINK_SOCKET", "SHLVL", "LC_TELEPHONE", 
	"LC_MEASUREMENT", "XDG_SESSION_ID", "XDG_RUNTIME_DIR", "LC_TIME", "XDG_DATA_DIRS", 
	"PATH", "DBUS_SESSION_BUS_ADDRESS", "UID", "LC_NUMERIC", NULL};
	while (names[i])
	{
		dict_add(&(line->env), ft_strdup(names[i]), ft_strdup(getenv(names[i])));
		i++;
	}
	dict_add(&(line->env), ft_strdup("?"), ft_strdup("0"));
}

void	init_struct(t_line *line)
{
	line->pip_in = NULL;
	line->pip_out = NULL;
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	line->is_newline = TRUE;
	line->command = NULL;
	line->args = NULL;
	line->redir_input = NULL;
	line->redir_output = NULL;
}

void	func_dict_init(t_line *line)
{
	line->func_dict = NULL;

	t_func *pwd;
	pwd = malloc(sizeof(t_func));
	pwd->foo = execute_pwd;
	dict_add(&(line->func_dict), ft_strdup("pwd"), pwd);

	t_func *cd;
	cd = malloc(sizeof(t_func));
	cd->foo = execute_cd;
	dict_add(&(line->func_dict), ft_strdup("cd"), cd);

	t_func *echo;
	echo = malloc(sizeof(t_func));
	echo->foo = execute_echo;
	dict_add(&(line->func_dict), ft_strdup("echo"), echo);

	t_func *env;
	env = malloc(sizeof(t_func));
	env->foo = execute_env;
	dict_add(&(line->func_dict), ft_strdup("env"), env);

	t_func *export;
	export = malloc(sizeof(t_func));
	export->foo = execute_export;
	dict_add(&(line->func_dict), ft_strdup("export"), export);

	t_func *cat;
	cat = malloc(sizeof(t_func));
	cat->foo = execute_cat;
	dict_add(&(line->func_dict), ft_strdup("cat"), cat);
}

