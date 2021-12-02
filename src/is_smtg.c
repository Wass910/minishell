/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_smtg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:45 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:46 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_quott(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_red(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

int	is_echo(char *s)
{
	if (!s[0] || !s[1] || !s[2] || !s[3])
		return (0);
	if (s[0] == 'e' && s[1] == 'c' && s[2] == 'h'
		&& s[3] == 'o' && (s[4] == ' ' || s[4] == '\0'))
		return (1);
	else
		return (0);
}
