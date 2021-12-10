/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:02 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/10 10:26:23 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_builtin(char **str)
{
	if ((ft_strncmp(str[0], "cd", 2) == 0) && ft_strlen(str[0]) == 2)
		return (CD_TYPE);
	else if ((ft_strncmp(str[0], "echo", 4) == 0) && ft_strlen(str[0]) == 4)
		return (ECHO_TYPE);
	else if ((ft_strncmp(str[0], "pwd", 3) == 0) && ft_strlen(str[0]) == 3)
		return (PWD_TYPE);
	else if ((ft_strncmp(str[0], "export", 6) == 0) && ft_strlen(str[0]) == 6)
		return (EXPORT_TYPE);
	else if ((ft_strncmp(str[0], "unset", 5) == 0) && ft_strlen(str[0]) == 5)
		return (UNSET_TYPE);
	else if ((ft_strncmp(str[0], "env", 3) == 0) && ft_strlen(str[0]) == 3)
		return (ENV_TYPE);
	else if ((ft_strncmp(str[0], "exit", 4) == 0) && ft_strlen(str[0]) == 4)
		return (EXIT_TYPE);
	return (-1);
}

int	builtin(char **cmd, t_list **a_list, t_list **b_list)
{
	int	type;

	type = find_builtin(cmd);
	if (type == CD_TYPE)
		type = build_cd(cmd);
	else if (type == ECHO_TYPE)
		type = build_echo(cmd);
	else if (type == PWD_TYPE)
		type = build_pwd();
	else if (type == EXPORT_TYPE)
		type = build_export(cmd, a_list, b_list);
	else if (type == UNSET_TYPE)
		type = build_unset(cmd, a_list, b_list, 0);
	else if (type == ENV_TYPE)
		type = build_env(a_list);
	else if (type == EXIT_TYPE)
		type = build_exit(cmd, a_list, b_list);
	if (type)
	{
		g_line.retval = type;
		return (type);
	}
	return (0);
}
