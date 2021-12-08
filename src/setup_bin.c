/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:00 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/08 11:17:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_open	open_setup(t_open open)
{
	open.to_write = -1;
	open.to_read = -1;
	return (open);
}

char	*build_sret(char *sret, char *s)
{
	char	*temp;

	temp = malloc(sizeof(char) * 300);
	if (!temp)
		return (NULL);
	temp[0] = '"';
	temp[1] = '"';
	temp[2] = '\0';
	sret = ft_strcat_ns(s, temp);
	free(temp);
	free(s);
	return (sret);
}
