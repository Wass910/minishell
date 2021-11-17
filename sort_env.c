#include "minishell.h"

void sort_env(t_list **b_list)
{
    t_list *temp;
    char *swap;

    temp = (*b_list);
    while (check_sorted(b_list))
    {
        while (temp->next)
        {
            if (temp->content[11] > temp->next->content[11])
            {
                swap = temp->content;
                temp->content = temp->next->content;
                temp->next->content = swap;
            }
            temp = temp->next;
        }
        temp = (*b_list);
    }
}

int check_sorted(t_list **b_list)
{
    t_list *temp;

    temp = (*b_list);
    while (temp->next)
    {
        if (temp->content[11] > temp->next->content[11])
            return (1);
        temp = temp->next;
    }
    return (0);
}

void print_env(t_list **b_list)
{
    t_list *temp;

    temp = (*b_list);
    while (temp->next)
    {
        printf("%s\n", temp->content);
        temp = temp->next;
    }
    printf("%s\n", temp->content);
}

char *to_print(char *s)
{
    int i;
    char *sret;
    char *temp;

    i = 0;
    temp = malloc(sizeof(char) * 1000);
    if (!temp)
        return (NULL);
    while (s[i] != '=' && s[i])
        i++;
    if (s[i] == '\0')
    {
        free(temp);
        return (s);
    }
    if (s[i] == '=' && s[i + 1] == '\0')
    {
        temp[0] = '"';
        temp[1] = '"';
        temp[2] = '\0';
        sret = ft_strcat_ns(s, temp);
        free(temp);
        return (sret);
    }
    else
    {
        sret = ft_strcat_cote(s, "\0");
        free(temp);
        return (sret);
    }
}

void add_line(t_list **b_list, t_comm comm, int j)
{
    int i;
    char *str;

    i = 0;
    str = to_print(comm.cmd[j]);
    if(!is_alphanum(str))
    {
        printf("export: '%s': not a valid identifier\n", str);
        return ;
    }
    flstadd_back(b_list, flstnew(ft_strcat("declare -x", str)));
    sort_env(b_list);
}