#include "minishell.h"

char *to_print2(char *s)
{
    int i;
    char *sret;
    char *temp;

    i = 0;
    temp = malloc(sizeof(char) * 100);
    if (!temp)
        return (NULL);
    while (s[i] != '=' && s[i] != '\0')
        i++;
    if (s[i] == '\0')
    {
        return (NULL);
    }
    else
	{
		free(temp);
		return (s);
	}
}

void add_line2(t_list **b_list, t_comm comm)
{
    int i;
    char *str;

    i = 0;
    str = to_print2(comm.cmd[1]);
	if (str)
    	flstadd_back(b_list, flstnew(str));
}