/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:57:17 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 17:19:36 by glaverdu         ###   ########.fr       */
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

char	*ft_strdup_free(char *s1)
{
	char	*cpy;
	int		i;

	i = ft_strlen((char *)s1);
	cpy = malloc(sizeof(char) * (i + 1));
	if (!(cpy))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	free(s1);
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
