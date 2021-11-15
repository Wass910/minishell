#include "minishell.h"

int build_unset(t_comm comm)
{
    //test by exporting an env variable and deleting it, check if export n unset work on env
    char *str;
    int i;
    int j;

    i = 1;
    j = 0;
    str = comm.cmd[i];
    while (comm.cmd[i])
    {
        str = ft_strcat_ns(comm.cmd[i], "=");
        while (ft_strncmp(str, comm.env[j], ft_strlen(str)) != 0 && comm.env[j])
        {
            j++;
        }
        if (comm.env[j])
            comm.env[j] = NULL;
        i++;
        j = 0;
        str = comm.cmd[i];
    }
}

int build_env(t_comm comm)
{
    int i;

    i = 0;
    while (comm.env[i])
    {
        printf("%s\n", comm.env[i]);
        i++;
    }
    return (0);
}

int build_exit(t_comm comm)
{

}