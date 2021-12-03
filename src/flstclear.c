/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flstclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:59 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:00 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	flstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	if (del)
	{
		while (*lst)
		{
			del((*lst)->content);
			tmp = (*lst);
			*lst = (*lst)->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
