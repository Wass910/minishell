/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:03 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/08 16:29:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list(t_list **a_list)
{
	t_list	*temp;

	while ((*a_list)->next)
	{
		temp = (*a_list);
		(*a_list) = (*a_list)->next;
		free(temp);
	}
	free(*a_list);
}
