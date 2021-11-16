/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:57:17 by glaverdu          #+#    #+#             */
/*   Updated: 2021/01/08 13:23:26 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;

	i = ft_strlen((char *)s1);
	if (!(cpy = malloc(sizeof(char) * (i + 1))))
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

char **make_expenv(t_comm comm)
{
	int i;
	char **envv;

	i = 0;
	while (comm.env[i])
		i++;
	envv = malloc(sizeof(char *) * i + 1);
	envv[i] = NULL;
	if (!envv)
		return (NULL);
	i = 0;
	while (comm.env[i])
	{
		envv[i] = malloc(sizeof(char) * ft_strlen(comm.env[i]) + 11);
		if (!envv[i])
			return (NULL);
		envv[i] = ft_strdup(comm.env[i]);
		i++;
	}
	return (envv);
}
