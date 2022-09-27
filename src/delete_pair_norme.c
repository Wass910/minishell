/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_pair_norme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:59:15 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/10 18:05:44 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_del	*delete_pair_setup_del(t_del *del)
{
	del = malloc(sizeof(t_del) * 1);
	del->j = 0;
	del->i = 0;
	del->k = 0;
	del->c = 0;
	del->str = malloc(sizeof(char) * 1000);
	if (!del->str)
		exit(EXIT_FAILURE);
	del->temp = malloc(sizeof(char) * 500);
	if (!del->temp)
		exit(EXIT_FAILURE);
	del->temp2 = malloc(sizeof(char *) * 5);
	if (!del->temp2)
		exit(EXIT_FAILURE);
	return (del);
}

void	delete_pair_norm(char *s, t_del *del)
{
	if (s[del->i] == 34 || s[del->i] == 39)
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
	}
	else
		del->temp[0] = '\0';
	del->k = 0;
}

void	delete_pair_norm4(char *s, t_del *del, t_list **a_list)
{
	if (s[del->i] == '$' && s[del->i + 1] && char_alphanum(s[del->i + 1]))
	{
		del->temp2[0] = after_env(&s[del->i]);
		del->temp2[1] = getenv2(del->temp2[0], a_list);
		while (del->temp2[1][del->c])
		{
			del->str[del->j] = del->temp2[1][del->c];
			del->c++;
			del->j++;
		}
		del->c = 0;
		if (del->temp2[1])
		{
			del->i++;
			while (s[del->i] && char_alphanum(s[del->i]))
				del->i++;
		}
		free_both(del);
	}
	else
	{
		del->str[del->j] = s[del->i];
		del->j++;
		del->i++;
	}
}

void	delete_pair_norm2(char *s, t_del *del, t_list **a_list)
{
	del->k++;
	if (&del->temp[del->k])
		del->temp2[0] = after_env(&del->temp[del->k]);
	del->temp2[1] = getenv2(del->temp2[0], a_list);
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
	free(del->temp2[0]);
	free(del->temp2[1]);
}

void	delete_pair_norm_while(char *s, t_del *del, t_list **a_list)
{
	if (del->temp[del->k] == '$' && del->temp[del->k + 1]
		&& char_alphanum(del->temp[del->k + 1]) && del->type == 34)
		delete_pair_norm2(s, del, a_list);
	else if (del->temp[del->k])
	{
		del->str[del->j] = del->temp[del->k];
		del->k++;
		del->j++;
	}
}
