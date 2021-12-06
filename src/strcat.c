/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:52:46 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/06 11:19:21 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strcat_w(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	j = 0;
	tmp[i] = '/';
	i++;
	while (src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		++j;
	}
	tmp[i++] = '\0';
	return (tmp);
}

char	*ft_strcat_redf(char *dest, char *src)
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
	while (src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		++j;
	}
	tmp[i++] = '\0';
	return (tmp);
}

char	*ft_strcat_red(char *dest, char *src)
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
	j = 0;
	while (src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		++j;
	}
	tmp[i++] = '\0';
	return (tmp);
}

char	*ft_strcat_cmd(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = malloc(sizeof(char) * (ft_count_str(dest, src) + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (dest[i] != '\0')
	{
		tmp[i] = dest[i];
		i++;
	}
	j = 0;
	tmp[i] = '/';
	i++;
	while (src[j] != '\0')
	{
		tmp[i] = src[j];
		i++;
		++j;
	}
	tmp[i++] = '\0';
	return (tmp);
}
