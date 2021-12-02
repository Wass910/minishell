/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:32 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:06:33 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*str;

	if (!s || !*s || start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	str = malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(int count, int size)
{
	void			*result;
	unsigned char	*tmp;
	int				i;
	int				n;

	i = 0;
	if (count == 0)
		return (ft_strdup(""));
	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	tmp = result;
	n = count * size;
	while (n > 0)
	{
		*tmp = (unsigned char)i;
		tmp[i] = '\0';
		tmp++;
		n--;
	}
	return (result);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (s[a] != '\0')
		a++;
	if (c == '\0')
		return (s + a);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

int	ft_count(char *s1, char *s2)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[e] != '\0')
	{
		e++;
		i++;
	}
	i = i + 2;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2, int f)
{
	int		e;
	int		i;
	char	*str;

	f++;
	e = 0;
	i = ft_count(s1, s2);
	str = malloc(sizeof(*str) * i);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[e] != '\0')
	{
		str[i] = s2[e];
		i++;
		e++;
	}
	free(s1);
	str[i] = '\0';
	return (str);
}
