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

int check_doll(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

int char_alphanum(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

char *after_env(char *s)
{
    char *temp;
    int i;
    int c;

    i = 0;
    c = 0;
    temp = malloc(sizeof(char) * 1000);
    if (!temp)
        return (NULL);
    if (s[i] == '$')
        i++;
    while (char_alphanum(s[i]))
    {
        temp[c] = s[i];
        i++;
        c++;
    }
    temp[c] = '\0';
    return (temp);
}

char *fill_doll(char *s, t_list **a_list)
{
    char *str;
    char *temp;
    char *temp2;
    int i;
    int c;
    int j;

    i = 0;
    c = 0;
    j = 0;
    str = malloc(sizeof(char) * 1000);
    if (!str)
        return (NULL);
    while (s[i])
    {
        while (s[i] && s[i] != '$')
        {
            str[j] = s[i];
            j++;
            i++;
        }
        if (s[i + 1] && (char_alphanum(s[i + 1]) || s[i + 1] == '?'))
        {
            if (s[i + 1] == '?' && !s[i + 2])
                return (s);
            temp = after_env(&s[i]);
            temp2 = getenv2(temp, a_list);
            free(temp);
            while (temp2 && temp2[c])
            {
                str[j] = temp2[c];
                j++;
                c++;
            }
            i++;
            while (char_alphanum(s[i]))
                i++;
            c = 0;
            free(temp2);
        }
        else{
            str[j] = '$';
            j++;
            i++;
        }
    }
    str[j] = '\0';
    free(s);
    return (str);
}

int unclosed_quotes(char *s)
{
    int i;
    int j;
    int type;

    i = 0;
    j = 0;
    type = 0;
    while (s[i])
    {
        if (s[i] == 34 || s[i] == 39)
        {
            type = s[i];
            i++;
            while (s[i] && s[i] != type)
                i++;
            if (!s[i])
                return(1);
        }
        i++;
    }
    return (0);
}