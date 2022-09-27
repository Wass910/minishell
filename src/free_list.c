/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:47:24 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 11:29:56 by idhiba           ###   ########.fr       */
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
		free(temp->content);
		free(temp);
	}
	free((*a_list)->content);
	free(*a_list);
}
