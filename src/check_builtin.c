/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:26 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/02 14:05:27 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verif_the_builtin(char **str)
{
	if ((ft_strncmp(str[0], "cd", 2) == 0) && ft_strlen(str[0]) == 2)
		return (0);
	else if ((ft_strncmp(str[0], "echo", 4) == 0) && ft_strlen(str[0]) == 4)
		return (0);
	else if ((ft_strncmp(str[0], "pwd", 3) == 0) && ft_strlen(str[0]) == 3)
		return (0);
	else if ((ft_strncmp(str[0], "export", 6) == 0) && ft_strlen(str[0]) == 6)
		return (0);
	else if ((ft_strncmp(str[0], "unset", 5) == 0) && ft_strlen(str[0]) == 5)
		return (0);
	else if ((ft_strncmp(str[0], "env", 3) == 0) && ft_strlen(str[0]) == 3)
		return (0);
	else if ((ft_strncmp(str[0], "exit", 4) == 0) && ft_strlen(str[0]) == 4)
		return (0);
	return (1);
}

int	if_builtin(char **str)
{
	if (verif_the_builtin(str) == 1)
		return (1);
	return (0);
}
