/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:01 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:05:02 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_unset	unset_setup(t_unset unset, char **cmd, t_list **a_list, t_list **b_list)
{
	unset.str = unset_str(cmd[unset.i]);
	unset.temp = unset_tlist(a_list, b_list, unset.type);
	unset.s = unset_s(unset.temp, unset.type);
	return (unset);
}

t_unset	unset_loop_setup(t_unset unset)
{
	while (unset.temp->next)
	{
		if (unset.type == 0)
			unset.s = &unset.temp->next->content[11];
		else
			unset.s = unset.temp->next->content;
		if (is_same(unset.s, unset.str) == 0)
			break ;
		unset.temp = unset.temp->next;
	}
	return (unset);
}

int	unset_loop(t_unset unset, t_list **a_list, t_list **b_list, char **cmd)
{
	while (cmd[unset.i])
	{
		unset = unset_setup(unset, cmd, a_list, b_list);
		if (is_same(unset.s, unset.str) == 0)
		{
			(*b_list) = (*b_list)->next;
			if (cmd[unset.i + 1])
			{
				unset.i++;
				unset.str = cmd[unset.i];
			}
			else
				return (0);
		}
		unset = unset_loop_setup(unset);
		if (is_same(unset.s, unset.str) == 0)
		{
			unset.del = unset.temp->next;
			unset.temp->next = unset.temp->next->next;
		}
		unset.i++;
		unset.str = cmd[unset.i];
	}
	return (1);
}

int	build_unset(char **cmd, t_list **a_list, t_list **b_list, int type)
{
	t_unset	unset;

	unset.i = 1;
	unset.type = type;
	unset.str = cmd[1];
	unset.s = malloc(sizeof(char) * 1000);
	if (!unset.s)
		return (1);
	if (!unset_loop(unset, a_list, b_list, cmd))
		return (0);
	if (type == 0)
		build_unset(cmd, a_list, b_list, 1);
	return (0);
}
