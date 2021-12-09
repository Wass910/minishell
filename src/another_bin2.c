/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_bin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:07 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 10:53:53 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_n_free(t_list *del, char *s, char *str, t_list *temp)
{
	del = temp->next;
	temp->next = temp->next->next;
	free(del->content);
	free(del);
	free(str);
	free(s);
	return ;
}

void	replace_n_free2(t_list *del, char *s, char *str, t_list *temp)
{
	del = temp->next;
	temp->next = temp->next->next;
	free(del->content);
	free(del);
	free(str);
	free(s);
	return ;
}

void	replace_n_free3(t_list *temp, char *s, char *str, t_list **a_list)
{
	temp = (*a_list);
	(*a_list) = (*a_list)->next;
	free(temp->content);
	free(temp);
	free(s);
	free(str);
	return ;
}
