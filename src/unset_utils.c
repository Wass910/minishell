/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:06 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:07:07 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*unset_str(char *cmd)
{
	if (cmd[1] == '=')
		return (ft_strcat_ns(cmd, "="));
	else
		return (cmd);
}

t_list	*unset_tlist(t_list **a_list, t_list **b_list, int type)
{
	if (type == 0)
		return ((*b_list));
	else
		return ((*a_list));
}

char	*unset_s(t_list *temp, int type)
{
	if (type == 0)
		return (&temp->content[11]);
	else
		return (temp->content);
}
