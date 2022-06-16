/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnickole <hnickole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:34:14 by atifany           #+#    #+#             */
/*   Updated: 2022/05/27 17:40:40 by hnickole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/minishell.h"

char	ft_switch(t_line *line)
{
	if (!ft_strcmp(line->command, "exit"))
	{
		clear_struct(line);
		return (1);
	}
	if (!ft_strncmp(line->command, "./", 2) || *(line->command) == '/'){
		execute_file(line->args);
		return (0);
	}
	func *f = dict_get(&(line->func_dict), line->command);
	if (!f)
	{
		printf("%s is not recognised as command\n", line->command);
		return (0);
	}
	printf("%s", f->foo(line));
	return (0);
}

void	sighandler(int sig)
{
	(void)sig;
	if (child_pid != 0)
	{
		kill(child_pid, SIGINT);
		write(1, "\n", 1);
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

char **_init_env()
{
	char *save;
	int i =0;
	char *names[] = {"SHELL", "SESSION_MANAGER", "QT_ACCESSIBILITY", "COLORTERM", "GNOME_DESKTOP_SESSION_ID", 
	"LANGUAGE", "LC_ADDRESS", "LC_NAME", "SSH_AUTH_SOCK", "CINNAMON_VERSION", "LC_MONETARY", 
	"SSH_AGENT_PID", "CINNAMON_SLOWDOWN_FACTOR", "GTK_MODULES", "PWD", "LOGNAME", "QT_QPA_PLATFORMTHEME", 
	"XDG_SESSION_TYPE", "GPG_AGENT_INFO", "PULSE_SCRIPT", "GJS_DEBUG_TOPICS", "HOME", "LC_PAPER", "LANG", 
	"LS_COLORS", "XDG_CURRENT_DESKTOP", "VTE_VERSION", "XRDP_SOCKET_PATH", "XRDP_PULSE_SOURCE_SOCKET", 
	"GNOME_TERMINAL_SCREEN", "GJS_DEBUG_OUTPUT", "LESSCLOSE", "XDG_SESSION_CLASS", "TERM", 
	"LC_IDENTIFICATION", "GTK_OVERLAY_SCROLLING", "LESSOPEN", "USER", "CINNAMON_SOFTWARE_RENDERING", 
	"GNOME_TERMINAL_SERVICE", "XRDP_SESSION", "DISPLAY", "XRDP_PULSE_SINK_SOCKET", "SHLVL", "LC_TELEPHONE", 
	"LC_MEASUREMENT", "XDG_SESSION_ID", "XDG_RUNTIME_DIR", "LC_TIME", "XDG_DATA_DIRS", 
	"PATH", "DBUS_SESSION_BUS_ADDRESS", "UID", "LC_NUMERIC", "_", NULL};
	while (names[i])
	{
		names[i] = ft_strdup(names[i]);
		save = ft_strdup(names[i]);
		names[i] = gnl_join(&(names[i]), "=", 1);
		names[i] = gnl_join(&(names[i]),
			getenv(save), ft_strlen(getenv(save)));
		printf("%s\n", names[i]);
		//write(1, getenv(names[i]), ft_strlen(getenv(names[i])));
		//write(1, "\n", 1);
		i++;
	}
	return (names);
}

int	main()
{
	char	rotate;
	t_line	line;
	//t_list *env;
	//t_list *shell;
	//char **names = _init_env();

	func_dict_init(&(line.func_dict));
	child_pid = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);

	init_struct(&line);
	rotate = 0;
	while (!rotate)
	{
		rotate = process_input(&line);
	}
	rl_clear_history();
	return (0);
}
