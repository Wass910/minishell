/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:47:24 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/09 10:26:54 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	build_pwd(void)
{
	char	*str;
	char	s[100];

	str = getcwd(s, 100);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (str == NULL)
		return (1);
	return (0);
}
