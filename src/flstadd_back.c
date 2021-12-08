/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flstadd_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:56 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:05:57 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	flstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;

	if (!(*alst))
	{
		(*alst) = new;
		return ;
	}
	begin = (*alst);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}
