/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:31 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 19:36:12 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*fill_doll_norm(t_doll *doll)
{
	char	*s;

	doll->str[doll->j] = '\0';
	s = ft_strdup_free(doll->str);
	free(doll);
	return (s);
}
