/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:07 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/06 19:39:54 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	only_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != 32 && s[i] != 9)
			return (0);
		i++;
	}
	return (1);
}

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

	while (temp->next)
	{
		s = setup_s(s, temp, j);
		if (!is_same(s, str) || !is_same(str, s))
			break ;
		temp = temp->next;
	}
	if ((!is_same(s, str) || !is_same(str, s)) && j == 1)
	{
		del = temp->next;
		temp->next = temp->next->next;
		free_part(del, s);
		return ;
	}
	if ((!is_same(s, str) || !is_same(str, s)) && is_valid(str))
	{
		del = temp->next;
		temp->next = temp->next->next;
		free_part(del, s);
		return ;
	}
	free(s);
}

void	already_in(t_list **a_list, char *str, int j)
{
	t_list	*temp;
	char	*s;

	temp = (*a_list);
	str = make_test(str);
	if (j == 1)
		s = &temp->content[11];
	else
		s = temp->content;
	s = make_test(s);
	if (!is_same(s, str) && j == 1)
	{
		temp = (*a_list);
		(*a_list) = (*a_list)->next;
		free(temp);
		return ;
	}
	if (!is_same(s, str) && is_valid(str))
	{
		temp = (*a_list);
		(*a_list) = (*a_list)->next;
		free(temp);
		return ;
	}
	next_part(temp, j, s, str);
	free(s);
}
