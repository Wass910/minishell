/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:04:35 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 17:11:27 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_del	*setup_del(void)
{
	t_del	*del;

	del = malloc(sizeof(t_del) * 1);
	if (!del)
		exit(EXIT_FAILURE);
	del->j = 0;
	del->i = 0;
	del->k = 0;
	del->c = 0;
	del->temp2 = malloc(sizeof(char *) * 3);
	del->str = malloc(sizeof(char) * 1000);
	if (!del->str)
		exit(EXIT_FAILURE);
	del->temp = malloc(sizeof(char) * 1000);
	if (!del->temp)
		exit(EXIT_FAILURE);
	return (del);
}

void	del_if1(t_del *del, char *s)
{
	del->type = s[del->i];
	del->i++;
	while (s[del->i] && s[del->i] != del->type)
	{
		del->temp[del->k] = s[del->i];
		del->k++;
		del->i++;
	}
	del->temp[del->k] = '\0';
	del->i++;
	del->k = 0;
}

void	del_if2(t_del *del, char *s, t_list **a_list)
{
	del->k++;
	del->temp2[0] = after_env(&del->temp[del->k]);
	del->temp2[1] = getenv2(del->temp2[0], a_list);
	free(del->temp2[0]);
	if (!del->temp2[1])
	{
		del->str[del->j] = s[del->i];
		del->i++;
		del->j++;
	}
	while (del->temp2[1] && del->temp2[1][del->c])
	{
		del->str[del->j] = del->temp2[1][del->c];
		del->c++;
		del->j++;
	}
	del->c = 0;
	if (del->temp2[1])
	{
		while (del->temp[del->k] && char_alphanum(del->temp[del->k]))
			del->k++;
	}
	free(del->temp2[1]);
}

void	del_if3(t_del *del, char *s, t_list **a_list)
{
	char	*temp;
	char	*temp2;

	temp = after_env(&s[del->i]);
	temp2 = getenv2(temp, a_list);
	while (temp2 && temp2[del->c])
	{
		del->str[del->j] = temp2[del->c];
		del->c++;
		del->j++;
	}
	del->c = 0;
	if (temp2 && temp2[1])
	{
		del->i++;
		while (s[del->i] && char_alphanum(s[del->i]))
			del->i++;
	}
	if (temp2)
		free(temp2);
}

void	del_else(t_del *del)
{
	del->str[del->j] = del->temp[del->k];
	del->k++;
	del->j++;
}
