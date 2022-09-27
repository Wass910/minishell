/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:12 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 16:04:42 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*to_print2(char *s)
{
	int		i;
	char	*sret;

	i = 0;
	if (s[i] == '=')
	{
		sret = malloc(sizeof(char) * 1);
		if (!sret)
			exit(EXIT_FAILURE);
		sret[0] = '\0';
		free(s);
		return (sret);
	}
	while (s[i] != '=' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	else
		return (s);
}

void	add_line2(t_list **b_list, char **cmd, int j)
{
	int		i;
	char	*str;

	i = 0;
	str = to_print2(ft_strdup(cmd[j]));
	if (str)
	{
		if (!is_alphanum(str))
		{
			printf("export: '%s': not a valid identifier\n", str);
			free(str);
			return ;
		}
	}
	if (str && str[0])
		flstadd_back(b_list, flstnew(str));
	if (str && !str[0])
		free(str);
}

char	*getenv2(char *s, t_list **a_list)
{
	t_list	*temp;
	char	*str;

	temp = (*a_list);
	while (temp->next)
	{
		if (!is_same(temp->content, s))
		{
			str = ft_strcat_ns(&temp->content[ft_strlen(s) + 1], NULL);
			return (str);
		}
		temp = temp->next;
	}
	if (!is_same(temp->content, s))
	{
		str = ft_strcat_ns(&temp->content[ft_strlen(s) + 1], NULL);
		return (str);
	}
	return (NULL);
}

int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '\0')
		return (0);
	return (1);
}

char	*make_test(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * 100);
	if (!str)
		exit(EXIT_FAILURE);
	while (s[i] != '=' && s[i])
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
