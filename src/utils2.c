/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:12 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:07:13 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*to_print2(char *s)
{
	int		i;
	char	*temp;

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

void	add_line2(t_list **b_list, char **cmd, int j)
{
	int		i;
	char	*str;

	i = 0;
	str = to_print2(cmd[j]);
	if (str)
	{
		if (!is_alphanum(str))
		{
			printf("export: '%s': not a valid identifier\n", str);
			return ;
		}
	}
	if (str)
		flstadd_back(b_list, flstnew(str));
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
		return (NULL);
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
