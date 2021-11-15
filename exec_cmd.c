#include "minishell.h"

void    exec_cmd(char *s, t_comm comm)
{
    execve(s, comm.cmd, NULL);
}

int build_cd(t_comm comm)
{
    int i;
    char *str;
    char *s;

    if (comm.cmd[1][0] == '~' && comm.cmd[1][1] == '\0')
    {
        str = getenv("HOME");
        if (!str)
            return (-1);
        i = chdir(str);
    }
    else if (comm.cmd[1][0] == '~' && comm.cmd[1][1] == '/')
    {
        s = malloc(100);
        if (!s)
            return (-1);
        str = getenv("HOME");
        if (!str)
            return (-1);
        i = 1;
        while (comm.cmd[1][i])
        {
            s[i - 1] = comm.cmd[1][i];
            i++;
        }
        s[i - 1] = '\0';
        str = ft_strjoin(str, s);
        i = chdir(str);
        if (i == -1)
        {
            str = strerror(errno);
            write(1, str, ft_strlen(str));
        }
        free(s);
        return (i);
    }
    else
        i = chdir(comm.cmd[1]);
    if (i == -1)
    {
        str = strerror(errno);
        write(1, str, ft_strlen(str));
    }
    return (i);
}

int build_echo(t_comm comm)
{
    int i;
    char *str;

    if (strncmp(comm.cmd[1], "-n", 2) == 0 && !check_fulln(comm.cmd[1]))
    {
        i = 2;
        while (comm.cmd[i])
        {
            if (check_inenv(comm.cmd[i]))
            {
                str = getenv(&comm.cmd[i][1]);
                write(1, str, ft_strlen(str));
            }
            else
                write(1, comm.cmd[i], ft_strlen(comm.cmd[i]));
            if (comm.cmd[i + 1])
                write(1, " ", 1);
            i++;
        }
    }
    else
    {
        i = 1;
        while (comm.cmd[i])
        {
            if (check_inenv(comm.cmd[i]))
            {
                str = getenv(&comm.cmd[i][1]);
                write(1, str, ft_strlen(str));
            }
            else
                write(1, comm.cmd[1], ft_strlen(comm.cmd[1]));
            if (comm.cmd[i + 1])
                write(1, " ", 1);
            i++;
        }
        write(1, "\n", 1);
    }
}

int build_pwd(t_comm comm)
{
    char *str;
    char s[100];

    str = getcwd(s, 100);
    write(1, str, ft_strlen(str));
    write(1, "\n", 1);
    if (str == NULL)
        return (1);
    return (0);
}

int build_export(t_comm comm)
{

}