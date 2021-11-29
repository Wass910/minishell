#include "../inc/minishell.h"

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

void add_line2(t_list **b_list, char **cmd, int j)
{
    int i;
    char *str;

    i = 0;
    str = to_print2(cmd[j]);
    if (str)
    {
        if(!is_alphanum(str))
        {
            printf("export: '%s': not a valid identifier\n", str);
            return ;
        }
    }
	if (str)
    	flstadd_back(b_list, flstnew(str));
}

char *getenv2(char *s, t_list **a_list)
{
    t_list *temp;
    char *str;

    temp = (*a_list);
    while (temp->next)
    {
        if (!is_same(temp->content, s))
        {
            str = ft_strcat_ns(&temp->content[ft_strlen(s)], NULL);
            return (str);
        }
        temp = temp->next;
    }
    if (!is_same(temp->content, s))
    {
        str = ft_strcat_ns(&temp->content[ft_strlen(s)], NULL);
        return (str);
    }
    return (NULL);
}

int is_valid(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    if (s[i] == '\0')
        return (0);
    return (1);
}

char    *make_test(char *s)
{
    int i;
    char *str;

    i = 0;
    str = malloc(sizeof(char) * 100);
    if (!str)
        return (NULL);
    while(s[i] != '=' && s[i])
    {
        str[i] = s[i];
        i++;
    }
    if (s[i] == '=')
    {
        str[i] = '=';
        i++;
    }
    str[i] = '\0';
    return (str);
}

void    already_in(t_list **a_list, char *str, int j)
{
    t_list *temp;
    t_list *del;
    char *s;

    temp = (*a_list);
    str = make_test(str);
    if(j == 1)
        s = &temp->content[11];
    else
        s = temp->content;
    s = make_test(s);
    if(!is_same(s, str) && j == 1)
    {
        temp = (*a_list);
        (*a_list) = (*a_list)->next;
        free(temp);
        return ;
    }
    if(!is_same(s, str) && is_valid(str))
    {
        temp = (*a_list);
        (*a_list) = (*a_list)->next;
        free(temp);
        return ;
    }
    while (temp->next)
    {
        if(j == 1)
            s = &temp->next->content[11];
        else
            s = temp->next->content;
        s = make_test(s);
        if(!is_same(s, str) || !is_same(str, s))
        {
            break;
        }
        temp = temp->next;
    }
    if ((!is_same(s, str) || !is_same(str, s))&& j == 1)
    {
        del = temp->next;
        temp->next = temp->next->next;
        free(del);
        free(s);
        return ;
    }
    if ((!is_same(s, str) || !is_same(str, s)) && is_valid(str))
    {
        del = temp->next;
        temp->next = temp->next->next;
        free(del);
        free(s);
        return ;
    }
    free(s);
}