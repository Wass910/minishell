/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:54 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/06 11:36:28 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
        else
            temp[0] = '\0';
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

char *ft_split_command_quote(char **str)
{
	char *cmd;
	int i;
	int j;
	int count;

	j = 0;
	i = 0;
	i = 2;
    if (str[0] && str[1])
        cmd = ft_strcat_redf(str[0], str[1]);
    if (str[0] && !str[1])
        return ft_strdup(str[0]);
	while(str[i])
	{
		cmd = ft_strcat_redf(cmd, str[i]);
        i++;
	}
	return cmd;
}

char *parse_quotes(char **s, t_list **a_list)
{
    int i;
    int j;
    char *cmd;

    i = 0;
    j = 0;
    while (s[i])
    {
        if (no_quotes(s[i]))
        {
            if (check_doll(s[i]))
                s[i] = fill_doll(s[i], a_list);
            if (s[i][0] == '\0')
                s[i] = NULL;
        }
        else
        {
            if (unclosed_quotes(s[i]))
            {
                printf("Unclosed quotes, check your inport before retrying\n");
                return (NULL);
            }
            s[i] = delete_pair(s[i], a_list);
        }
        i++;
    }
    cmd = ft_split_command_quote(s);
    free_str(s);
    return (cmd);
}