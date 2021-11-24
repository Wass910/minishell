#include "../inc/minishell.h"

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
    if (!str)
        return (NULL);
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

char *delete_pair(char *s, t_list **a_list)
{
    int i;
    int j;
    int k;
    int c;
    int type;
    char *str;
    char *temp;
    char *temp2[2];

    j = 0;
    i = 0;
    k = 0;
    c = 0;
    str = malloc(sizeof(char) * 1000);
    if (!str)
        return (NULL);
    temp = malloc(sizeof(char) * 1000);
    if (!temp)
        return (NULL);
    while (s[i])
    {
        k = 0;
        if (s[i] == 34 || s[i] == 39)
        {
            type = s[i];
            i++;
            while (s[i] && s[i] != type)
            {
                temp[k] = s[i];
                //printf("s[i] = %c\n", s[k]);
                k++;
                i++;
            }
            temp[k] = '\0';
            i++;
            //printf("temp = %s\n", temp);
        }
        k = 0;
        while (temp && temp[k])
        {
            if (temp[k] == '$' && temp[k + 1] && char_alphanum(temp[k + 1]) && type == 34)
            {
                k++;
                temp2[0] = after_env(&temp[k]);
                temp2[1] = getenv2(temp2[0], a_list);
                free(temp2[0]);
                if (!temp2[1])
                {
                    str[j] = s[i];
                    i++;
                    j++;
                }
                while (temp2[1] && temp2[1][c])
                {
                    str[j] = temp2[1][c];
                    c++;
                    j++;
                }
                c = 0;
                if (temp2[1])
                {
                    while(temp[k] && char_alphanum(temp[k]))
                        k++;
                }
                free(temp2[1]);
            }
            else if (temp[k])
            {
                str[j] = temp[k];
                k++;
                j++;
            }
        }
        temp[0] = '\0';
        if (s[i] && s[i] != 34 && s[i] != 39)
        {
            if (s[i] == '$' && s[i + 1] && char_alphanum(s[i + 1]))
            {
                temp2[0] = after_env(&s[i]);
                temp2[1] = getenv2(temp2[0], a_list);
                free(temp2[0]);
                while (temp2[1][c])
                {
                    str[j] = temp2[1][c];
                    c++;
                    j++;
                }
                c = 0;
                if (temp2[1])
                {
                    i++;
                    while(s[i] && char_alphanum(s[i]))
                        i++;
                }
                free(temp2[1]);
            }
            else
            {
                str[j] = s[i];
                j++;
                i++;
            }
        }
    }
    free(temp);
    free(s);
    str[j] = '\0';
    return (str);
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
        //j = pair_quotes(s);
        //if (j == 3)
        //{
         //   if (no_cross(s))
         //       return(app_nocross(s, a_list));
        //}
        s = delete_pair(s, a_list);
    }
    return (s);
}