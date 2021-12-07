/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:04:42 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/07 13:33:03 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	del_else2(t_del *del, char *s)
{
	del->str[del->j] = s[del->i];
	del->j++;
	del->i++;
}

void	del_if4(t_del *del, char *s, t_list **a_list)
{
	if (s[del->i] == '$' && s[del->i + 1] && char_alphanum(s[del->i + 1]))
		del_if3(del, s, a_list);
	else
		del_else2(del, s);
}

void	del_free(t_del *del, char *s)
{
	free(del->temp);
	free(s);
}

int	verif_pipe(char *str)
{
	int	i;
	int	pipe;

	pipe = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			pipe = i + 1;
			if (str[i + 1] == '|')
				return (1);
			while (str[pipe] == 32)
				pipe++;
			if (str[pipe] == '|' || !str[pipe])
				return (1);
		}
		i++;
	}
	return (0);
}

int	only_in_quotes(char *s)
{
	int	i;
	int	type;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			type = s[i];
			i++;
			while (s[i] != type && s[i])
			{
				if (s[i] == 124)
					s[i] = 23;
				i++;
			}
		}
		i++;
	}
	return (0);
}
