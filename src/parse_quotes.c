#include "../inc/minishell.h"

int no_quotes(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == 34 || s[i] == 39)
            return (0);
        i++;
    }
    return (1);
}

int closing_quotes(char *s)
{
    int i;
    int type;

    i = 0;
    if (s[i] == 39 || s[i] == 34)
    {
        if (s[i] == 39)
            type = 39;
        if (s[i] == 34)
            type = 34;
        i++;
    }
    while (s[i] != 39 && s[i] != 34 && s[i])
        i++;
    if (s[i] == 39 && type == 39 && !s[i + 1])
        return (1);
    if (s[i] == 34 && type == 34 && !s[i + 1])
        return (1);
    else
        return (0);
}

char *fill_closing(char *s, t_list **a_list)
{
    int i;
    int j;
    char *str;
    int type;

    i = 0;
    j = 0;
    str = malloc(sizeof(char) * 1000);
    if (!str)
        return (NULL);
    if (s[i] == 34)
        type = 34;
    else
        type = 39;
    i++;
    while (s[i] != type)
    {
        str[j] = s[i];
        i++;
        j++;
    }
    str[j] = '\0';
    if (type == 34 && check_inenv(&str[1], a_list))
        str = getenv(&str[1]);
    free(s);
    return (str);
}

int check_doll(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '$')
            return (i);
        i++;
    }
    return (-1);
}

char *parse_quotes(char *s, t_list **a_list)
{
    int i;
    int j;
    char *str;
    char *temp;
    int doll;

    i = 0;
    j = 0;
    if (no_quotes(s))
    {
        doll = check_doll(s);
        if (doll >= 0)
        {
            temp = malloc(sizeof(char) * 1000);
            if (!temp)
                return (NULL);
            while (s[j] != '$')
            {
                temp[j] = s[j];
                j++;
            }
            temp[j] = '\0';
            printf("%s\n", temp);
            free(s);
            free(temp);
            return (str);
        }
        return (s);
    }
    if (closing_quotes(s))
        return (fill_closing(s, a_list));
    return (NULL);
}