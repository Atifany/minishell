#include "sources/_headers/minishell.h"

void	_redirect_output(int **pip, char mode){
	static int	save_out_stream;

	if (mode == INIT){
		save_out_stream = dup(STDOUT_FILENO);
		*pip = (int *)malloc(sizeof(int) * 2);
		pipe(*pip);
	}
	else if (mode == OPEN){
		
		//printf("Rerouted output to pip_out\n");
		dup2((*pip)[WRITE], STDOUT_FILENO);
	}
	else if (mode == CLOSE){
		dup2(save_out_stream, STDOUT_FILENO);
		//printf("Rerouted output to stdout\n");
		//write((*pip)[WRITE], "\0", 1);
		close((*pip)[WRITE]);
		close((*pip)[READ]);
		//printf("Sent pipe contents to recievers\n");
	}
}

static void	_redirect_input(int **pip, char mode){
	static int	save_in_stream;

	if (mode == INIT){
		save_in_stream = dup(STDIN_FILENO);
		*pip = (int *)malloc(sizeof(int) * 2);
		pipe(*pip);
	}
	else if (mode == OPEN){
		dup2((*pip)[READ], STDIN_FILENO);
	}
	else if (mode == CLOSE && *pip){
		close((*pip)[READ]);
		close((*pip)[WRITE]);
		dup2(save_in_stream, STDIN_FILENO);
		free(*pip);
		*pip = NULL;
	}
}

char **_init_env()
{
	char *save;
	int i =0;
	char *_names[] = {"SHELL", "SESSION_MANAGER", "QT_ACCESSIBILITY", "COLORTERM", "GNOME_DESKTOP_SESSION_ID", 
	"LANGUAGE", "LC_ADDRESS", "LC_NAME", "SSH_AUTH_SOCK", "CINNAMON_VERSION", "LC_MONETARY", 
	"SSH_AGENT_PID", "CINNAMON_SLOWDOWN_FACTOR", "GTK_MODULES", "PWD", "LOGNAME", "QT_QPA_PLATFORMTHEME", 
	"XDG_SESSION_TYPE", "GPG_AGENT_INFO", "PULSE_SCRIPT", "GJS_DEBUG_TOPICS", "HOME", "LC_PAPER", "LANG", 
	"LS_COLORS", "XDG_CURRENT_DESKTOP", "VTE_VERSION", "XRDP_SOCKET_PATH", "XRDP_PULSE_SOURCE_SOCKET", 
	"GNOME_TERMINAL_SCREEN", "GJS_DEBUG_OUTPUT", "LESSCLOSE", "XDG_SESSION_CLASS", "TERM", 
	"LC_IDENTIFICATION", "GTK_OVERLAY_SCROLLING", "LESSOPEN", "USER", "CINNAMON_SOFTWARE_RENDERING", 
	"GNOME_TERMINAL_SERVICE", "XRDP_SESSION", "DISPLAY", "XRDP_PULSE_SINK_SOCKET", "SHLVL", "LC_TELEPHONE", 
	"LC_MEASUREMENT", "XDG_SESSION_ID", "XDG_RUNTIME_DIR", "LC_TIME", "XDG_DATA_DIRS", 
	"PATH", "DBUS_SESSION_BUS_ADDRESS", "UID", "LC_NUMERIC", "_", NULL};
	char **names = ft_calloc(sizeof(char *), 56);
	while (_names[i])
	{
		names[i] = ft_strdup(_names[i]);
		save = ft_strdup(_names[i]);
		names[i] = gnl_join(&(names[i]), "=", 1);
		names[i] = gnl_join(&(names[i]),
			getenv(save), ft_strlen(getenv(save)));
		//printf("%s\n", names[i]);
		i++;
	}
	return (names);
}

static void	run_minishell(int *pip_in){
	char **names = _init_env();
	execve("minishell", NULL, names);
}

static void ft_print(char *str){
	int i = 0;
	if (!str){
		return ;
	}
	while (str[i]){
		if (str[i] == '\n'){
			write(1, "\\n", 2);
		}
		else if (str[i] == '\t'){
			write(1, "\\t", 2);
		}
		else{
			write(1, &(str[i]), 1);
		}
		i++;
	}
}

static void exp_vs_ret(char *expected, char *ret){
	write(1, "Expected: \"", 12);
	ft_print(expected);
	write(1, "\"\nRecieved: \"", 13);
	ft_print(ret);
	write(1, "\"", 1);
}

static int count_n(char *str){
	int i = 0;
	int lines_to_read = 1;

	while (str[i]){
		if (str[i] == '\n')
			lines_to_read++;
		i++;
	}
	if (str[i-1] == '\n')
		lines_to_read--;
	return (lines_to_read);
}

static void output(char *ret, char *expected, char *cmd){
	if (ft_strcmp(ret, expected)){
		write(1, RED, ft_strlen(GRN));
		write(1, "[X]", 3);
		write(1, NC, ft_strlen(NC));
		write(1, " cmd: \"", 7);
		ft_print(cmd);
		write(1, "\"\n", 2);
		exp_vs_ret(expected, ret);
	}
	else{
		write(1, GRN, ft_strlen(GRN));
		write(1, "[V]", 3);
		write(1, NC, ft_strlen(NC));
		write(1, " cmd: \"", 7);
		ft_print(cmd);
		write(1, "\"", 1);
		//exp_vs_ret(expected, ret);
	}
	write(1, "\n", 1);
}

static char check_if_in(char *str, char **to_search){
	int where = -1;
	int i = 0;
	while (to_search[i]){
		where = ft_strnstr(str, to_search[i], ft_strlen(str));
		if (where != ft_strlen(str)){
			return (where);
		}
		i++;
	}
	return (where);
}

char is_prompt_read = FALSE;

static char *gnl(int fd, char **dels){
	char *ret = NULL;
	char str[2];
	*str = 0; *(str + 1) = 0;

	//write(1, ">", 1);
	while (check_if_in(ret, dels) == ft_strlen(ret)){
		read(fd, &str, 1);
		//ft_print(str);
		ret = gnl_join(&ret, str, 1);
	}
	is_prompt_read = FALSE;
	//write(1, "<\n", 2);
	int where = check_if_in(ret, dels);
	if (where != ft_strlen(ret)){
		if (ret[where] == '\n'){
			ret = ft_substr(ret, 0, where + 1);
		}	
		else{
			is_prompt_read = TRUE;
			ret = ft_substr(ret, 0, where);
		}		
	}
	return (ret);
}

static char simple_cmp(int *pip_in, int *pip_out, \
	char *cmd, char *expected){
	
	char *dels[3] = {"\n",
		"\e[0;36mminishell \e[1;36m>> \e[0m", NULL};
	char str[2];
	ft_bzero(str, 2);
	char *ret = NULL;
	int i;
	int lines_to_read = 0;
	
	lines_to_read = count_n(cmd);

	write(pip_in[WRITE], cmd, ft_strlen(cmd));
	usleep(10000);
	//write(1, "|", 1);
	//ft_print(ret);
	//write(1, "|\n", 2);
	if (!is_prompt_read){
		ret = gnl(pip_out[READ], dels);
		//write(1, "|", 1);
		//ft_print(ret);
		//write(1, "|\n", 2);
	}
	ret = gnl(pip_out[READ], dels);
	//write(1, "|", 1);
	//ft_print(ret);
	//write(1, "|\n", 2);
	//if (*expected){
		ret = gnl(pip_out[READ], dels);
		//write(1, "|", 1);
		//ft_print(ret);
		//write(1, "|\n", 2);
	//}
	output(ret, expected, cmd);
}

static void go_tests(int *pip_in, int *pip_out){
	char *cmd;
	char *exp;
	int	id;

	printf("%sTest pwd:%s\n", YEL, NC);
	cmd = "pwd\n";
	exp = "/media/atifany/Local Disc E1/minishell\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "\t \tpwd   \n";
	exp = "/media/atifany/Local Disc E1/minishell\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "pwd ../\n";
	exp = "pwd: too many arguments\n";
	simple_cmp(pip_in, pip_out, cmd, exp);

	printf("%sTest echo:%s\n", YEL, NC);
	cmd = "echo ANIME MUST DIE\n";
	exp = "ANIME MUST DIE\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "echo -n ANIME MUST DIE\n";
	exp = "ANIME MUST DIE\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "echo -n\n";
	exp = "\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "echo\n";
	exp = "\n";
	simple_cmp(pip_in, pip_out, cmd, exp);

	printf("%sTest cd:%s\n", YEL, NC);
	cmd = "cd ../\n";
	exp = "\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "pwd\n";
	exp = "/media/atifany/Local Disc E1\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "cd $HOME\n";
	exp = "\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "pwd\n";
	exp = "/home/atifany\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "cd ../\n";
	exp = "\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "cd\n";
	exp = "\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "pwd\n";
	exp = "/home/atifany\n";
	simple_cmp(pip_in, pip_out, cmd, exp);

	printf("%sTest env:%s\n", YEL, NC);
	cmd = "export ANIME=MUST_DIE\n";
	exp = "\0";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "echo $ANIME\n";
	exp = "MUST_DIE\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "export =MUST_DIE\n";
	exp = "env: incorrect argument\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	cmd = "export ANIME=\n";
	exp = "env: incorrect argument\n";
	simple_cmp(pip_in, pip_out, cmd, exp);

	cmd = "export =\n";
	exp = "env: incorrect argument\n";
	simple_cmp(pip_in, pip_out, cmd, exp);
	
	cmd = "export\n";
	exp = "env: incorrect argument\n";
	simple_cmp(pip_in, pip_out, cmd, exp);

	//write(pip_in[WRITE], "export =\n", ft_strlen(cmd));
	//write(pip_in[WRITE], "env\n", ft_strlen(cmd));

	write(pip_in[WRITE], "exit\n", ft_strlen("exit\n"));
}

int main(int argc, char **argv)
{
    int *pip_in;
	int *pip_out;
	int status;

    printf("-->>--%sStarted testing%s--<<--\n", BBLU, NC);

	_redirect_input(&pip_in, INIT);
	_redirect_output(&pip_out, INIT);
	_redirect_input(&pip_in, OPEN);
    int id_mini = fork();
    if (id_mini == 0){
		_redirect_output(&pip_out, OPEN);
        run_minishell(pip_in);
		_redirect_output(&pip_out, CLOSE);
        exit(0);
    }
    else{
		int id_test = fork();
		if (id_test == 0){
			go_tests(pip_in, pip_out);
			exit(0);
		}
		else{
        	waitpid(id_mini, &status, 0);
			if (WIFSIGNALED(status))
			{
    			// It was terminated by a signal
    			if (WTERMSIG(status) == SIGSEGV)
    			{
					printf("%sSIGSEGV%s\n", YEL, NC);
					kill(id_test, SIGINT);
  				}
			}
		printf("-->>--%sFinished testing%s--<<--\n", BBLU, NC);
		}
    }
	_redirect_input(&pip_in, CLOSE);
}