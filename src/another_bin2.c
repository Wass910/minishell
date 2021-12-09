/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_bin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:07 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 23:12:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_n_free(t_list *del, char *s, char *str, t_list *temp)
{
	del = temp->next;
	temp->next = temp->next->next;
	if (del->content)
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
	if (del->content)
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
	if (temp->content)
		free(temp->content);
	free(temp);
	free(s);
	free(str);
	return ;
}

int	ft_count_str(char *s1, char *s2)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s1 != NULL && s1[i] != '\0')
		i++;
	while (s2 && s2[e] != '\0')
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}