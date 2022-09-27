/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:07 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 17:11:13 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_part(t_list *del, char *s)
{
	free(del);
	free(s);
}

char	*setup_s(char *s, t_list *temp, int j)
{
	if (j == 1)
		s = &temp->next->content[11];
	else
		s = temp->next->content;
	s = make_test(s);
	return (s);
}

void	next_part(t_list *temp, int j, char *s, char *str)
{
	t_list	*del;

	del = NULL;
	while (temp->next)
	{
		s = setup_s(s, temp, j);
		if (!is_same(s, str) || !is_same(str, s))
			break ;
		temp = temp->next;
		if (temp->next)
			free(s);
	}
	if ((!is_same(s, str) || !is_same(str, s)) && j == 1)
	{
		replace_n_free(del, s, str, temp);
		return ;
	}
	if ((!is_same(s, str) || !is_same(str, s)) && is_valid(str))
	{
		replace_n_free2(del, s, str, temp);
		return ;
	}
	free(str);
	free(s);
}

void	already_in(t_list **a_list, char *str, int j)
{
	t_list	*temp;
	char	*s;

	temp = (*a_list);
	s = NULL;
	str = make_test(str);
	s = fill_s(s, j, temp);
	s = make_test(s);
	if (!is_same(s, str) && j == 1)
	{
		replace_n_free3(temp, s, str, a_list);
		return ;
	}
	if (!is_same(s, str) && is_valid(str))
	{
		replace_n_free3(temp, s, str, a_list);
		return ;
	}
	free(s);
	next_part(temp, j, s, str);
}
