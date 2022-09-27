/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:09 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 16:05:12 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_fulln(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	check_inenv(char *str, t_list **a_list)
{
	t_list	*temp;

	temp = (*a_list);
	while (temp->next)
	{
		if (!is_same(temp->content, str))
			return (1);
		temp = temp->next;
	}
	if (!is_same(temp->content, str))
		return (1);
	return (0);
}

void	make_list(t_list **a_list, char **envp)
{
	int	i;

	i = 0;
	(*a_list) = flstnew(ft_strdup(envp[i]));
	i++;
	(*a_list)->next = NULL;
	while (envp[i])
	{
		flstadd_back(a_list, flstnew(ft_strdup(envp[i])));
		i++;
	}
}

void	add_declare(t_list **b_list)
{
	t_list	*temp;

	temp = (*b_list);
	while (temp->next)
	{
		temp->content = ft_strcat_free("declare -x", temp->content);
		temp = temp->next;
	}
	temp->content = ft_strcat_free("declare -x", temp->content);
}

int	is_alphanum(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=' && s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a'
				|| s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z') && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
