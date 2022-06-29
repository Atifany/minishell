#include "sources/_headers/minishell.h"

void    sigint_hook(int sig)
{
    write(1, "OPA!\n", 5);
    exit(0);
}

void    sigint_hook_1(int sig)
{
    write(1, "OPA1!\n", 6);
    exit(0);
}

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, sigint_hook);
        while (TRUE);
        exit (0);
    }
    else
    {
        signal(SIGINT, sigint_hook_1);
        wait(NULL);
    }
}