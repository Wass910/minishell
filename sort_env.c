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

void add_line(t_list **b_list, t_comm comm)
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