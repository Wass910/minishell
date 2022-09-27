/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:02 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 16:24:59 by idhiba           ###   ########.fr       */
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
	if (s[i] == '=')
	{
		printf("export : << %s >> : invalid identifier\n", s);
		sret = malloc(sizeof(char) * 1);
		if (!sret)
			exit(EXIT_FAILURE);
		sret[0] = '\0';
		free(s);
		return (sret);
	}
	while (s[i] != '=' && s[i])
		i++;
	if (s[i] == '\0')
		return (s);
	if (s[i] == '=' && s[i + 1] == '\0')
		return (build_sret(sret, s));
	else
		return (sret_ret(s, sret));
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
	if (str && str[0])
		flstadd_back(b_list, flstnew2(ft_strcat("declare -x", str)));
	sort_env(b_list);
	free(str);
}
