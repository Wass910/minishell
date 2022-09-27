/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flstnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:06:04 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 17:07:11 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strcpy(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = NULL;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_list	*flstnew2(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	free(content);
	new->next = NULL;
	return (new);
}

t_list	*flstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
