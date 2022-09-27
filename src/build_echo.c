/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:04:57 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/09 20:02:21 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_returnvalue(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '$' && s[1] == '?' && s[2] == '\0')
		return (1);
	return (0);
}

void	cut_echo(char **cmd, int i, char *str)
{
	while (cmd[i])
	{
		if (is_returnvalue(cmd[i]))
		{
			str = ft_itoa(g_line.retval);
			write(1, str, ft_strlen(str));
		}
		else
			write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	cut_echo2(char **cmd, int i, char *str)
{
	while (cmd[i])
	{
		if (is_returnvalue(cmd[i]))
		{
			str = ft_itoa(g_line.retval);
			write(1, str, ft_strlen(str));
			free(str);
		}
		else
			write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	build_echo(char **cmd)
{
	char	*str;

	str = NULL;
	if (!cmd[1])
	{
		printf("\n");
		return (0);
	}
	if (strncmp(cmd[1], "-n", 2) == 0 && !check_fulln(cmd[1]))
		cut_echo(cmd, 2, str);
	else
		cut_echo2(cmd, 1, str);
	return (0);
}
