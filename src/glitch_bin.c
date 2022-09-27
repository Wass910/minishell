/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glitch_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:39 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 16:28:01 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lred	*fill_dred(void)
{
	t_lred	*dred;

	dred = malloc(sizeof(t_lred) * 1);
	if (!dred)
		exit(EXIT_FAILURE);
	dred = dred_setup(dred, 1);
	return (dred);
}

t_doll	*doll_cut(t_doll *doll, char *s, t_list **a_list)
{
	doll->temp = after_env(&s[doll->i]);
	doll->temp2 = getenv2(doll->temp, a_list);
	free(doll->temp);
	while (doll->temp2 != NULL && doll->temp2[doll->c])
	{
		doll->str[doll->j] = doll->temp2[doll->c];
		doll->j++;
		doll->c++;
	}
	doll->i++;
	while (s[doll->i] && char_alphanum2(s[doll->i]))
		doll->i++;
	doll->c = 0;
	free(doll->temp2);
	return (doll);
}

int	unclosed_quotes(char *s)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	type = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			type = s[i];
			i++;
			while (s[i] && s[i] != type)
				i++;
			if (!s[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	char_alphanum2(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

t_doll	*doll_setup(t_doll *doll)
{
	doll = malloc(sizeof(t_doll) * 1);
	if (!doll)
		exit(EXIT_FAILURE);
	doll->i = 0;
	doll->j = 0;
	doll->c = 0;
	doll->str = malloc(sizeof(char) * 500);
	if (!doll->str)
		exit(EXIT_FAILURE);
	return (doll);
}
