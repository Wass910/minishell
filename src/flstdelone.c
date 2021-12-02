/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flstdelone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:00 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:01 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	flstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}
