/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:48:40 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:11 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_atoi(const char *str)
{
	char	*s1;
	int		i;
	int		neg;
	long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	s1 = (char *)str;
	while (s1[i] == '\f' || s1[i] == '\t' || s1[i] == '\n'
		|| s1[i] == '\r' || s1[i] == '\v' || s1[i] == ' ')
		i++;
	if (s1[i] == '+' || s1[i] == '-')
	{
		if (s1[i] == '-')
			neg = -1;
		i++;
	}
	while (s1[i] >= '0' && s1[i] <= '9')
	{
		nbr = nbr * 10 + (s1[i] - 48);
		i++;
	}
	return (nbr * neg);
}
