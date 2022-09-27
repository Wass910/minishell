/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:35 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 18:31:47 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_same(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] != s2[j])
			break ;
		i++;
		j++;
	}
	if (s1[i] == '=' && s2[j] == '\0')
		return (0);
	if (s1[i] == '\0' && s2[j] == '\0')
		return (0);
	return (1);
}

int	build_env(t_list **a_list)
{
	t_list	*temp;

	temp = (*a_list);
	while (temp->next)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	printf("%s\n", temp->content);
	return (0);
}

int	build_exit(char **cmd, t_list **a_list, t_list **b_list)
{
	int	i;

	free_list(a_list);
	free_list(b_list);
	free(g_line.str);
	if (cmd[1])
	{
		i = ft_atoi(cmd[1]);
		if (cmd[1][0] != '0' && i == 0)
		{
			printf("exit : %s: numeric argument required\n", cmd[1]);
			exit(2);
		}
		else
			printf("exit\n");
		exit(i);
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
