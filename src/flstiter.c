/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flstiter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:01 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:02 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	flstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	if (f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
