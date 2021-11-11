#include "minishell.h"


int verif_the_builtin(char **str)
{
    if ((ft_strncmp(str[1], "cd", 2) == 0) && ft_strlen(str[1]) == 2)
    {
        
        printf("The command is cd.\n");
        return 0;
    }
    else if ((ft_strncmp(str[1], "echo", 4) == 0) && ft_strlen(str[1]) == 4)
    {    
        printf("The command is echo.\n");
        if (str[2] && ((ft_strncmp(str[2], "-n", 2) != 0) || 
            ft_strlen(str[2]) != 2))
        {
                printf("Bad argument for echo.\n");
                exit(EXIT_FAILURE);
        }
        return 0;
    }
    else if ((ft_strncmp(str[1], "pwd", 3) == 0) && ft_strlen(str[1]) == 3)
    {
        printf("The command is pwd.\n");
        return 0;
    }
    else if ((ft_strncmp(str[1], "export", 6) == 0) && ft_strlen(str[1]) == 6)
    {
        printf("The command is export.\n");
        return 0;
    }
    else if ((ft_strncmp(str[1], "unset", 5) == 0) && ft_strlen(str[1]) == 5)
    {
        printf("The command is unset.\n");
        return 0;
    }
    else if ((ft_strncmp(str[1], "env", 3) == 0) && ft_strlen(str[1]) == 3)
    {
        printf("The command is env.\n");
        return 0;
    }
    else if ((ft_strncmp(str[1], "exit", 4) == 0) && ft_strlen(str[1]) == 4)
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
        printf("Command not found.\n");
        return 1;
    }
    return 0;

}