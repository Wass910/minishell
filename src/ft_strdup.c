/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:57:17 by glaverdu          #+#    #+#             */
/*   Updated: 2021/11/30 16:18:38 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;

	i = ft_strlen((char *)s1);
	cpy = malloc(sizeof(char) * (i + 1));
	if (!(cpy))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**make_expenv(t_comm comm)
{
	int		i;
	char	**temp;

	i = 0;
	while (comm.env[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (comm.env[i])
	{
		temp[i] = ft_strcat("declare -x", comm.env[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
