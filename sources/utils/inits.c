#include "../_headers/minishell.h"

void	clear_struct(t_line *line)
{
	if (line->command)
		free(line->command);
	if (line->args)
		free_array(line->args);
	if (line->fd_to_write)
		free_array(line->fd_to_write);
	if (line->fd_to_appwrite)
		free_array(line->fd_to_appwrite);
	if (line->redir_input)
		free_struct_array(line->redir_input);
	if (line->pip_in)
		free(line->pip_in);
	if (line->pip_out)
		free(line->pip_out);
}

void init_env(t_list **env)
{
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
	"PATH", "DBUS_SESSION_BUS_ADDRESS", "UID", "LC_NUMERIC", NULL};
	while (names[i])
	{
		dict_add(env, ft_strdup(names[i]), getenv(names[i]));
		i++;
	}
	dict_add(env, ft_strdup("?"), ft_strdup("0"));
}

void	init_struct(t_line *line)
{
	line->pip_in = NULL;
	line->pip_out = NULL;
	line->is_redirecting = FALSE;
	line->is_piping = FALSE;
	line->command = NULL;
	line->args = NULL;
	line->redir_input = NULL;
	line->fd_to_write = NULL;
	line->fd_to_appwrite = NULL;
	line->is_appending = FALSE;
}

void	func_dict_init(t_list **func_dict)
{
	*func_dict = NULL;

	func *pwd;
	pwd = malloc(sizeof(func));
	pwd->foo = execute_pwd;
	dict_add(func_dict, ft_strdup("pwd"), pwd);

	func *cd;
	cd = malloc(sizeof(func));
	cd->foo = execute_cd;
	dict_add(func_dict, ft_strdup("cd"), cd);

	func *echo;
	echo = malloc(sizeof(func));
	echo->foo = execute_echo;
	dict_add(func_dict, ft_strdup("echo"), echo);

	func *env;
	env = malloc(sizeof(func));
	env->foo = execute_env;
	dict_add(func_dict, ft_strdup("env"), env);

	func *export;
	export = malloc(sizeof(func));
	export->foo = execute_export;
	dict_add(func_dict, ft_strdup("export"), export);

	func *cat;
	cat = malloc(sizeof(func));
	cat->foo = execute_cat;
	dict_add(func_dict, ft_strdup("cat"), cat);
}

