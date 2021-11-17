#include "minishell.h"

int cote_count(char *s, int type)
{
    int i;
    int t2;

    i = 0;
    if (type == 34)
        t2 = 39;
    if (type == 39)
        t2 = 34;
    while (s[i] == type)
        i++;
    if (s[i] == t2)
        return(-1);
    return (i);
}

void    exec_cmd(char *s, t_comm comm)
{
    char *str;
    int i;
    int j;
    int stock[3];
    int sindex;

    i = 1;
    j = 0;
    sindex = 0;
    str = malloc(sizeof(char) * 100);
    if (!str)
        return ;
    while (comm.cmd[i])
    {
        if (comm.cmd[i][0] == 34)
        {
            stock[0] = cote_count(comm.cmd[i], 34);
            stock[1] = 0;
        }
        else if (comm.cmd[i][0] == 39)
        {
            stock[0] = cote_count(comm.cmd[i], 39);
            stock[1] = 1;
        }
        if (stock[0] == -1)
            break;
        if (stock[0])
        {
            while ((comm.cmd[i][j] == 34 || comm.cmd[i][j] == 39) && comm.cmd[i][j])
                j++;
            while ((comm.cmd[i][j] != 34 && comm.cmd[i][j] != 39) && comm.cmd[i][j])
            {
                str[sindex] = comm.cmd[i][j];
                j++;
                sindex++;
            }
            str[sindex] = '\0';
        }
        if ((comm.cmd[i][j] == 34 && stock[1] == 1) || (comm.cmd[i][j] == 39 && stock[1] == 0))
        {
            printf("Unclosed cotes, please check the input.\n");
            return ;
        }
        if (comm.cmd[i][j] == 34)
        {
            if(stock[0] != cote_count(&comm.cmd[i][j], 34))
            {
                printf("Unclosed cotes, please check the input.\n");
                return ;
            }
            else
            {
                comm.cmd[i] = str;
            }
        }
        if (comm.cmd[i][j] == 39)
        {
            if(stock[0] != cote_count(&comm.cmd[i][j], 39))
            {
                printf("Unclosed cotes, please check the input.\n");
                return ;
            }
            else
            {
                comm.cmd[i] = str;
            }
        }
        i++;
    }
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

int build_echo(t_comm comm, t_list **a_list)
{
    int i;
    char *str;

    if (strncmp(comm.cmd[1], "-n", 2) == 0 && !check_fulln(comm.cmd[1]))
    {
        i = 2;
        while (comm.cmd[i])
        {
            if (check_inenv(&comm.cmd[i][1], a_list))
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
            if (check_inenv(&comm.cmd[i][1], a_list))
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
    return (0);
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

int build_export(t_comm comm, t_list **a_list, t_list **b_list)
{
    static int done = 0;
    int i;

    i = 1;
    if (!done)
    {
        add_declare(b_list);
        done = 1;
    }
    if (check_sorted(b_list))
    {
        sort_env(b_list);
    }
    while (comm.cmd[i])
    {
        already_in(a_list, comm.cmd[i], 0);
        already_in(b_list, comm.cmd[i], 1);
        add_line(b_list, comm, i);
        add_line2(a_list, comm, i);
        i++;
    }
    if (!comm.cmd[1])
        print_env(b_list);
    return (0);
}