#include "minishell.h"

int find_builtin(char **str)
{
    //printf("str[0] = %s\n", str[0]);
    if ((ft_strncmp(str[0], "cd", 2) == 0) && ft_strlen(str[0]) == 2)
    {
        
        printf("The command is cd.\n");
        return CD_TYPE;
    }
    else if ((ft_strncmp(str[0], "echo", 4) == 0) && ft_strlen(str[0]) == 4)
    {    
        printf("The command is echo.\n");
        return ECHO_TYPE;
    }
    else if ((ft_strncmp(str[0], "pwd", 3) == 0) && ft_strlen(str[0]) == 3)
    {
        printf("The command is pwd.\n");
        return PWD_TYPE;
    }
    else if ((ft_strncmp(str[0], "export", 6) == 0) && ft_strlen(str[0]) == 6)
    {
        printf("The command is export.\n");
        return EXPORT_TYPE;
    }
    else if ((ft_strncmp(str[0], "unset", 5) == 0) && ft_strlen(str[0]) == 5)
    {
        printf("The command is unset.\n");
        return UNSET_TYPE;
    }
    else if ((ft_strncmp(str[0], "env", 3) == 0) && ft_strlen(str[0]) == 3)
    {
        printf("The command is env.\n");
        return ENV_TYPE;
    }
    else if ((ft_strncmp(str[0], "exit", 4) == 0) && ft_strlen(str[0]) == 4)
    {
        printf("The command is exit.\n");
        return EXIT_TYPE;
    }
    return (-1);
}

int    builtin(t_comm comm, t_list **a_list, t_list **b_list)
{
    int type;

    type = find_builtin(comm.cmd);
    if (type == CD_TYPE)
        return (build_cd(comm));
    else if (type == ECHO_TYPE)
        return(build_echo(comm));
    else if (type == PWD_TYPE)
        return(build_pwd(comm));
    else if (type == EXPORT_TYPE)
        return(build_export(comm, a_list, b_list));
    else if (type == UNSET_TYPE)
        return(build_unset(comm));
    else if (type == ENV_TYPE)
        return(build_env(comm, a_list));
    else if (type == EXIT_TYPE)
        return(build_exit(comm));
}