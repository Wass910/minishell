/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glitch_bin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:42 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:43 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_doll	*incr_doll(t_doll *doll)
{
	doll->str[doll->j] = '$';
	doll->j++;
	doll->i++;
	return (doll);
}

t_doll	*incr_doll2(t_doll *doll, char *s)
{
	doll->str[doll->j] = s[doll->i];
	doll->j++;
	doll->i++;
	return (doll);
}
