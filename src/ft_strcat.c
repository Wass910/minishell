/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:22 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/08 16:22:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_str(char *s1, char *s2)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s1 != NULL && s1[i] != '\0')
		i++;
	while (s2 && s2[e] != '\0')
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest && dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	tmp[i] = ' ';
	i++;
	j = 0;
	while (src && src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strcat_ns(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (dest && dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	j = 0;
	while (src && src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

t_cat	*cat_setup(char *dest, char *src)
{
	t_cat	*scat;

	scat = malloc(sizeof(t_cat) * 1);
	if (!scat)
		exit(EXIT_FAILURE);
	scat->i = 0;
	scat->k = 0;
	scat->j = 0;
	scat->tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 3));
	if (!scat->tmp)
		exit(EXIT_FAILURE);
	return (scat);
}

char	*ft_strcat_cote(char *dest, char *src)
{
	t_cat	*scat;
	char	*retstr;

	scat = cat_setup(dest, src);
	while (dest && dest[scat->k] != '\0')
	{
		if (scat->k >= 1 && dest[scat->k - 1] == '=')
		{
			scat->tmp[scat->i] = '"';
			scat->i++;
		}
		scat->tmp[scat->i] = dest[scat->k];
		scat->i++;
		scat->k++;
	}
	scat->tmp[scat->i] = '"';
	scat->i++;
	while (src && src[scat->j] != '\0')
		cat_while(scat, src);
	scat->tmp[scat->i] = '\0';
	retstr = ft_strdup(scat->tmp);
	free(scat->tmp);
	free(scat);
	return (retstr);
}
