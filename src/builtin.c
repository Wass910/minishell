#include "../inc/minishell.h"

int find_builtin(char **str)
{
    //printf("str[0] = %s\n", str[0]);
    if ((ft_strncmp(str[0], "cd", 2) == 0) && ft_strlen(str[0]) == 2)
    {
        
<<<<<<< HEAD
        //printf("The command is cd.\n");
=======
        printf("The command is cd.\n");
>>>>>>> main
        return CD_TYPE;
    }
    else if ((ft_strncmp(str[0], "echo", 4) == 0) && ft_strlen(str[0]) == 4)
    {    
<<<<<<< HEAD
        //printf("The command is echo.\n");
=======
        printf("The command is echo.\n");
>>>>>>> main
        return ECHO_TYPE;
    }
    else if ((ft_strncmp(str[0], "pwd", 3) == 0) && ft_strlen(str[0]) == 3)
    {
<<<<<<< HEAD
        //printf("The command is pwd.\n");
=======
        printf("The command is pwd.\n");
>>>>>>> main
        return PWD_TYPE;
    }
    else if ((ft_strncmp(str[0], "export", 6) == 0) && ft_strlen(str[0]) == 6)
    {
<<<<<<< HEAD
        //printf("The command is export.\n");
=======
        printf("The command is export.\n");
>>>>>>> main
        return EXPORT_TYPE;
    }
    else if ((ft_strncmp(str[0], "unset", 5) == 0) && ft_strlen(str[0]) == 5)
    {
<<<<<<< HEAD
        //printf("The command is unset.\n");
=======
        printf("The command is unset.\n");
>>>>>>> main
        return UNSET_TYPE;
    }
    else if ((ft_strncmp(str[0], "env", 3) == 0) && ft_strlen(str[0]) == 3)
    {
<<<<<<< HEAD
        //printf("The command is env.\n");
=======
        printf("The command is env.\n");
>>>>>>> main
        return ENV_TYPE;
    }
    else if ((ft_strncmp(str[0], "exit", 4) == 0) && ft_strlen(str[0]) == 4)
    {
<<<<<<< HEAD
        //printf("The command is exit.\n");
=======
        printf("The command is exit.\n");
>>>>>>> main
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
        return(build_echo(comm, a_list));
    else if (type == PWD_TYPE)
        return(build_pwd());
    else if (type == EXPORT_TYPE)
        return(build_export(comm, a_list, b_list));
    else if (type == UNSET_TYPE)
        return(build_unset(comm, a_list, b_list, 0));
    else if (type == ENV_TYPE)
        return(build_env(a_list));
    else if (type == EXIT_TYPE)
        return(build_exit(comm));
    return (0);
}