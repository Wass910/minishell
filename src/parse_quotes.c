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
        while (s[i] != '$')
        {
            str[j] = s[i];
            j++;
            i++;
        }
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
    str[j] = '\0';
    free(s);
    return (str);
}

int unclosed_quotes(char *s)
{
    int tab[1000];
    int i;
    int j;
    int mid;

    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] == 34 || s[i] == 39)
            j++;
        i++;
    }
    if (j % 2 != 0)
        return (1);
    j = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == 34)
            tab[j++] = 0;
        else if (s[i] == 39)
            tab[j++] = 1;
        i++;
    }
    i = 0;
    j--;
    mid = j / 2;
    while (i <= mid)
    {
        if (tab[i] != tab[j])
            return (1);
        i++;
        j--;
    }
    return (0);
}

int pair_quotes(char *s)
{
    int simple;
    int duble;
    int i;

    i = 0;
    simple = 0;
    duble = 0;
    while (s[i])
    {
        if (s[i] == 34)
            duble++;
        else if (s[i] == 39)
            simple++;
        i++;
    }
    //printf("simple = %d | duble = %d | simple / 2 = %d | duble / 2 == %d\n", simple, duble, (simple / 2), (duble / 2));
    if (!simple)
    {
        if ((duble / 2) % 2 == 0)
            return (2);
        else
            return (0);
    }
    if (!duble)
    {
        if ((simple / 2) % 2 == 0)
            return (1);
        else
            return (0);
    }
    if ((simple / 2) % 2 == 0 && (duble / 2) % 2 == 0)
        return (3);
    if ((simple / 2) % 2 != 0 && (duble / 2) % 2 == 0)
        return (2);
    if ((simple / 2) % 2 == 0 && (duble / 2) % 2 != 0)
        return (1);
    return (0);
}

int no_cross(char *s)
{
    int tab[1000];
    int i;
    int j;
    int mid;
    int change;

    j = 0;
    i = 0;
    change = 0;
    while (s[i])
    {
        if (s[i] == 34)
            tab[j++] = 0;
        else if (s[i] == 39)
            tab[j++] = 1;
        i++;
    }
    i = 0;
    j--;
    mid = j / 2;
    while (i <= mid)
    {
        if (tab[i] != tab[j])
            return (0);
        i++;
        j--;
        if (tab[i] != tab[i - 1])
            change++;
        if (change == 2)
            return (0);
    }
    return (1);
}

char *app_nocross(char *s, t_list **a_list)
{
    char *str;
    char *temp;
    char *temp2;
    int i;
    int j;
    int c;

    i = 0;
    j = 0;
    c = 0;
    temp = NULL;
    str = malloc(sizeof(char) * 1000);
    while (s[i])
    {
        if (s[i] && (s[i] == 34 || s[i] == 39))
            i++;
        else if (s[i] == '$')
        {
            i++;
            temp = after_env(&s[i]);
            temp2 = getenv2(temp, a_list);
            free(temp);
            if (temp2)
            {
                while (temp2[c])
                {
                    str[j] = temp2[c];
                    j++;
                    c++;
                }
                c = 0;
                free(temp2);
            }
            while (char_alphanum(s[i]))
                i++;
        }
        else if (s[i] != 34 && s[i] != 39)
        {
            str[j] = s[i];
            j++;
            i++;
        }
    }
    str[j] = '\0';
    free(s);
    return (str);
}

char *delete_pair(char*s)
{
    char *str;
    int type;
    int i;
    int j;
    int mid;
    int repeat;

    j = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == 34 || s[i] == 39)
            j++;
        i++;
    }
    i = 0;
    j--;
    mid = j / 2;
    str = malloc(sizeof(char) * 1000);
    if (!str)
        return (NULL);
    j = 0;
    while (i <= mid)
    {
        if (s[i] == 34 || s[i] == 39)
        {
            repeat = i;
            type = s[i];
            while (s[i] == type)
                i++;
        }
        //printf("type = %d | i = %d | repeat = %d | s[i] = %c\n", type, i, repeat, s[i]);
        if((i - repeat) % 2 == 0)
        {
            i = repeat;
            while (s[i] == type)
                i++;
        }
        else
        {
            i = repeat;
            //printf("type = %d | s[i] = %c\n", type, s[i]);
            while (s[i] == type)
            {
                str[j] = s[i];
                //printf("c = %c\n", str[j]);
                j++;
                i++;
            }
        }
        while (s[i] && s[i] != 39 && s[i] != 34)
        {
            str[j] = s[i];
            j++;
            i++;
        }
    }
    str[j] = '\0';
    printf("str = %s\n", str);
    return (NULL);
}

char *parse_quotes(char *s, t_list **a_list)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (no_quotes(s))
    {
        if (check_doll(s))
            s = fill_doll(s, a_list);
        return (s);
    }
    else
    {
        if (unclosed_quotes(s))
        {
            printf("Unclosed quotes, check your inport before retrying\n");
            return (NULL);
        }
        j = pair_quotes(s);
        printf("%d\n", j);
        if (j == 3)
        {
            if (no_cross(s))
                return(app_nocross(s, a_list));
        }
        s = delete_pair(s);
    }
    return (NULL);
}