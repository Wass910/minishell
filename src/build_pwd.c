/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:04:59 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:05:00 by glaverdu         ###   ########.fr       */
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
