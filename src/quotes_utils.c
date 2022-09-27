/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:58 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 17:39:23 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	no_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

int	check_doll(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	char_alphanum(char c)
{
	if (c >= 31 && c <= 127)
		return (1);
	return (0);
}

char	*after_env(char *s)
{
	char	*temp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	temp = malloc(sizeof(char) * 500);
	if (!temp)
		return (NULL);
	if (s[i] == '$')
		i++;
	while (char_alphanum2(s[i]))
	{
		temp[c] = s[i];
		i++;
		c++;
	}
	temp[c] = '\0';
	return (temp);
}

char	*fill_doll(char *s, t_list **a_list)
{
	t_doll	*doll;
	char	*str;

	doll = NULL;
	doll = doll_setup(doll);
	while (s[doll->i])
	{
		while (s[doll->i] && s[doll->i] != '$')
			doll = incr_doll2(doll, s);
		if (!s[doll->i])
			break ;
		if (s[doll->i + 1] && char_alphanum2(s[doll->i + 1]))
		{
			if (s[doll->i + 1] == '?' && !s[doll->i + 2])
				return (s);
			doll = doll_cut(doll, s, a_list);
			if (!s[doll->i])
				break ;
		}
		else
			doll = incr_doll(doll);
	}
	free(s);
	str = fill_doll_norm(doll);
	return (str);
}
