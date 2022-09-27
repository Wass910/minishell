/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flstadd_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:57 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:05:58 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	flstadd_front(t_list **alst, t_list *new)
{
	new->next = (*alst);
	*alst = new;
}
