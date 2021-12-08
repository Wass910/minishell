/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:02 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/08 11:18:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sort_env(t_list **b_list)
{
	t_list	*temp;
	char	*swap;

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

int	check_sorted(t_list **b_list)
{
	t_list	*temp;

	temp = (*b_list);
	while (temp->next)
	{
		if (temp->content[11] > temp->next->content[11])
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	print_env(t_list **b_list)
{
	t_list	*temp;

	temp = (*b_list);
	while (temp->next)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	printf("%s\n", temp->content);
}

char	*to_print(char *s)
{
	int		i;
	char	*sret;

	i = 0;
	sret = NULL;
	while (s[i] != '=' && s[i])
		i++;
	if (s[i] == '\0')
		return (s);
	if (s[i] == '=' && s[i + 1] == '\0')
		return (build_sret(sret, s));
	else
	{
		sret = ft_strcat_cote(s, "\0");
		free(s);
		return (sret);
	}
}

void	add_line(t_list **b_list, char **cmd, int j)
{
	int		i;
	char	*str;

	i = 0;
	str = to_print(ft_strdup(cmd[j]));
	if (!is_alphanum(str))
	{
		printf("export: '%s': not a valid identifier\n", str);
		free(str);
		return ;
	}
	flstadd_back(b_list, flstnew2(ft_strcat("declare -x", str)));
	sort_env(b_list);
	free(str);
}
