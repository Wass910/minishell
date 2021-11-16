#include "minishell.h"

int sort_env(char **env)
{
    int i;
    char *temp;

    i = 0;
    while (check_sorted(env))
    {
        if (env[i][11] > env[i + 1][11])
        {
            temp = env[i];
            env[i] = env[i + 1];
            env[i + 1] = temp;
        }
        i++;
        if (!env[i + 1])
            i = 0;
    }
    return (1);
}

int check_sorted(char **env)
{
    int i;

    i = 0;
    while (env[i + 1])
    {
        if (env[i][11] > env[i + 1][11])
            return (1);
        i++;
    }
    return (0);
}

void print_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        write(1, env[i], ft_strlen(env[i]));
        write(1, "\n", 1);
        i++;
    }
}

void add_line(t_comm comm)
{
    int i;

    i = 0;
    printf("wow\n");
    while (comm.env[i])
        i++;
    i++;
    comm.env[i] = comm.cmd[1];
    comm.env[i + 1] = NULL;
    i = 0;
    while(comm.expenv[i])
        i++;
    i++;
    comm.expenv[i] = comm.cmd[1];
    comm.expenv[i + 1] = NULL;
}