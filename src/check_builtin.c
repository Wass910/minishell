#include "../inc/minishell.h"


int verif_the_builtin(char **str)
{
    //printf("str[0] = %s\n", str[0]);
    if ((ft_strncmp(str[0], "cd", 2) == 0) && ft_strlen(str[0]) == 2)
    {
        
        printf("The command is cd.\n");
        return 0;
    }
    else if ((ft_strncmp(str[0], "echo", 4) == 0) && ft_strlen(str[0]) == 4)
    {    
        printf("The command is echo.\n");
        return 0;
    }
    else if ((ft_strncmp(str[0], "pwd", 3) == 0) && ft_strlen(str[0]) == 3)
    {
        printf("The command is pwd.\n");
        return 0;
    }
    else if ((ft_strncmp(str[0], "export", 6) == 0) && ft_strlen(str[0]) == 6)
    {
        printf("The command is export.\n");
        return 0;
    }
    else if ((ft_strncmp(str[0], "unset", 5) == 0) && ft_strlen(str[0]) == 5)
    {
        printf("The command is unset.\n");
        return 0;
    }
    else if ((ft_strncmp(str[0], "env", 3) == 0) && ft_strlen(str[0]) == 3)
    {
        printf("The command is env.\n");
        return 0;
    }
    else if ((ft_strncmp(str[0], "exit", 4) == 0) && ft_strlen(str[0]) == 4)
    {
        printf("The command is exit.\n");
        return 0;
    }
    return 1;
}

int if_builtin(char **str)
{
    if (verif_the_builtin(str) == 1)
    {
        printf("not builtin.\n");
        return 1;
    }
    return 0;

}